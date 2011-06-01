#ifndef ANS_INTERPRETER_HPP
#define ANS_INTERPRETER_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description:

usage:

struct echo {
    typedef void result_type;
    void operator ()(std::string const & s) const
    {
        std::cout << s << std::endl;
    }
};

void add(int a, int b)
{
    std::cout << a + b << std::endl;
}

void repeat(std::string const & s, int n)
{
    while (--n >= 0) std::cout << s;
    std::cout << std::endl; 
}

int main()
{
    ans::interpreter interpreter;
    
    interpreter.register_function<void(std::string const&)>("echo", echo());
    interpreter.register_function("echo2", &echo::operator (), echo());
    interpreter.register_function("add", &add);
    interpreter.register_function("repeat", & repeat);
    
    interpreter.register_function<void(int)>("add1", boost::bind(&add, 1, _1));

    std::string line = "nonempty";
    while (! line.empty())
    {
        std::cout << std::endl << "] ", std::getline(std::cin,line);

        try                          
        {
            interpreter.parse_input(line);
        }
        catch (std::runtime_error &error) 
        { 
            std::cerr << error.what() << std::endl; 
        }
    }

    return 0;
}
--------------------------------------------------------------------------------
*/

//////////////////////////////////////////////////////////////////////////

// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------
//
// This example implements a simple batch-style interpreter that is capable of
// calling functions previously registered with it. The parameter types of the
// functions are used to control the parsing of the input.
//
// Implementation description
// ==========================
//
// When a function is registered, an 'invoker' template is instantiated with
// the function's type. The 'invoker' fetches a value from the 'token_parser'
// for each parameter of the function into a tuple and finally invokes the the
// function with these values as arguments. The invoker's entrypoint, which
// is a function of the callable builtin that describes the function to call and
// a reference to the 'token_parser', is partially bound to the registered
// function and put into a map so it can be found by name during parsing.

#include <map>
#include <string>
#include <stdexcept>

#include <boost/token_iterator.hpp>
#include <boost/token_functions.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <boost/function.hpp>

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/function_traits.hpp>

#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/fusion/include/invoke.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/concept_check.hpp>
#include <boost/concept/requires.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/map.hpp>

#include <boost/function_types/is_nonmember_callable_builtin.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/function/function1.hpp>

namespace ans {

namespace fusion = boost::fusion;
namespace ft = boost::function_types;
namespace mpl = boost::mpl;

class interpreter
{
    class token_parser
    {
        typedef boost::token_iterator_generator<
            boost::char_separator<char> >::type token_iterator;

        token_iterator itr_at, itr_to;
    public:

        token_parser(token_iterator from, token_iterator to)
            : itr_at(from), itr_to(to)
        { }

    private:
        template<typename T>
        struct remove_cv_ref
            : boost::remove_cv< typename boost::remove_reference<T>::type >
        { };
    public:
        // Returns a token of given type.
        // We just apply boost::lexical_cast to whitespace separated string tokens
        // for simplicity.
        template<typename RequestedType>
        typename remove_cv_ref<RequestedType>::type get()
        {
            if (! this->has_more_tokens())
                throw std::runtime_error("unexpected end of input");

            try
            {
                typedef typename remove_cv_ref<RequestedType>::type result_type;
                result_type result = boost::lexical_cast
                    <typename remove_cv_ref<result_type>::type>(*this->itr_at);
                ++this->itr_at;
                return result;
            }

            catch (boost::bad_lexical_cast &)
            { throw std::runtime_error("invalid argument: " + *this->itr_at); }
        }

        // Any more tokens?
        bool has_more_tokens() const { return this->itr_at != this->itr_to; }
    };
    typedef boost::function<void(token_parser &)> invoker_function;
    typedef std::map<std::string, invoker_function> dictionary;

    dictionary map_invokers;

public:
    boost::function<void(const std::string&)> log;

    // Registers a function with the interpreter.
    template<typename Function>
    typename boost::enable_if<
        ft::is_nonmember_callable_builtin<Function>
    >::type register_function(std::string const & name, Function f) {
        // instantiate and store the invoker by name
        return register_nonmenber_impl<Function>(name, f);
    }
    
    // For functor.
    template<class Signature, typename Function>
    typename boost::disable_if<
        ft::is_callable_builtin<Function>
    >::type register_function(std::string const & name, Function f) {
        // Use boost.protect to prevent eval on f.
        return register_nonmenber_impl<
            typename boost::add_pointer<Signature>::type
        >(name, boost::protect(f));
    }
    
    // For member function.
    template<typename Function, typename Self>
    typename boost::enable_if<
        ft::is_member_function_pointer<Function>
    >::type register_function(std::string const& name, Function f, Self &self)
    {   
        // instantiate and store the invoker by name
        this->map_invokers[name] = boost::bind(
            &invoker<Function>::template apply_member<fusion::nil, Self>,
            f,
            &self, // note here, pass by value will cause the crush of TuorialApplication
            _1,
            fusion::nil()
        );
    }
    
    void remove_function(std::string const& name) {
        this->map_invokers.erase(name);
    }

    // Parse input for functions to call.
    void parse_input(std::string const & text) const
    {
        // [2011-2-15 14:46:18 by Answeror]
        // to support record
        if (log) log(text);
        
        boost::char_separator<char> s(" \t\n\r");

        token_parser parser
            ( boost::make_token_iterator<std::string>(text.begin(), text.end(), s)
            , boost::make_token_iterator<std::string>(text.end()  , text.end(), s) );

        // Note, if the input is "echo a echo a", the output will be "a\na\n",
        // so be careful with more than one function call in one line.
        // Maybe it has to be changed.
        while (parser.has_more_tokens())
        {
            // read function name
            std::string func_name = parser.get<std::string>();

            // look up function
            dictionary::const_iterator entry = map_invokers.find( func_name );
            if (entry == map_invokers.end())
                throw std::runtime_error("unknown function: " + func_name);

            // call the invoker which controls argument parsing
            entry->second(parser);
        }
    }
    
    template<class OutputIterator>
    BOOST_CONCEPT_REQUIRES(
        ((boost::OutputIterator<OutputIterator, std::string>)),
        (void)
    ) get_function_name(OutputIterator out) {
        boost::copy(
            this->map_invokers | boost::adaptors::map_keys, 
            out
        );
    }

public:
    template<class Signature, typename Function>
    void register_nonmenber_impl(std::string const & name, Function f)
    {
        // instantiate and store the invoker by name
        this->map_invokers[name] = boost::bind(
            &invoker<Function, Signature>::template apply<fusion::nil>,
            f,
            _1,
            fusion::nil()
        );
    }

private:
    template<
        typename Function,
        class Signature = Function,
        class From = typename mpl::begin<ft::parameter_types<Signature> >::type,
        class To = typename mpl::end<ft::parameter_types<Signature> >::type
    >
    struct invoker;
    
    template<typename Function, class Signature, class From, class To>
    struct invoker
    {
        // add an argument to a Fusion cons-list for each parameter type
        template<typename Args>
        static inline
            void apply(Function func, token_parser & parser, Args const & args)
        {
            typedef typename mpl::deref<From>::type arg_type;
            typedef typename mpl::next<From>::type next_iter_type;

            interpreter::invoker<Function, Signature, next_iter_type, To>::apply
                ( func, parser, fusion::push_back(args, parser.get<arg_type>()) );
        }
        
        template<typename Args, typename Self>
        static inline
            void apply_member(Function func, Self *self, token_parser & parser, Args const & args)
        {
            typedef typename mpl::next<From>::type next_iter_type;

            interpreter::invoker<Function, Signature, next_iter_type, To>::apply
                ( func, parser, fusion::push_back(args, self) );        
        }
    };

    template<typename Function, class Signature, class To>
    struct invoker<Function,Signature,To,To>
    {
        // the argument list is complete, now call the function
        template<typename Args>
        static inline
            void apply(Function func, token_parser &, Args const & args)
        {
            fusion::invoke(func,args);
        }
    };
};

} // ans

#endif
