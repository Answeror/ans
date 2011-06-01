#ifndef ANS_RESULT_ADAPTER_HPP
#define ANS_RESULT_ADAPTER_HPP

/*
@author: Answeror
@description:

Adapt function object to old style caller who use result_type.
And to solve the incompatibility of boost::tuple and boost::fusion.

e.g.

caller(result_adapter<fn(arg)>(fn()));
*/

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/utility/result_of.hpp>
//#include <boost/fusion/include/invoke.hpp>
#include <boost/mpl/at.hpp>

namespace ans {

// Sig: function call signature
template<class Sig>
struct result_adapter {
    // Because of the DSL nature of Sig, we use result_type to extract functor type.
    typedef typename boost::function_types::result_type<Sig>::type function_type;
    typedef typename boost::function_types::parameter_types<Sig>::type argument_type;
    typedef typename boost::result_of<Sig>::type result_type;
    
    function_type fn;
    
    result_adapter() {}
    
    result_adapter(const function_type &fn) : fn(fn) {}
    
    template<class T>
    result_type operator ()(T &t) const {
        // Use a type conversion to solve the incompatibility of boost::tuple
        // and boost::fusion.
        // Boost::tuple cannot be passed to ans::flatten directly.
        return fn(typename boost::mpl::at_c<argument_type, 0>::type(t));
    }
    
    template<class T>
    result_type operator ()(const T &t) const {
        return fn(typename boost::mpl::at_c<argument_type, 0>::type(t));
    }
};

} // ans

#endif
