#pragma once

/**
 * @file
 * @author answeror <answeror@gmail.com>
 * @date 2011-11-05
 * 
 * @section DESCRIPTION
 * 
 * This is a auto registered factory, inspired by boost.serialization.singleton.
 */

#include <map>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include <ans/factory_fwd.hpp>

namespace ans
{
    /**
     *  object factory
     *  
     *  Example:
     *  <pre><code>
     *  struct base
     *  {
     *      int x;
     *      base(int x) : x(x) {}
     *      virtual int f() const = 0;
     *  };
     *  
     *  typedef base * base_ptr;
     *  typedef std::unique_ptr<base> unique_base_ptr;
     *  typedef boost::shared_ptr<base> shared_base_ptr;
     *  
     *  struct foo : base
     *  {
     *      foo(int x) : base(x) {}
     *      int f() const { return x + 1; }
     *      static std::string identifier() { return "foo"; }
     *  
     *      void never_call_me()
     *      {
     *          ans::factory<base_ptr(int)>::register_product<foo>();
     *          ans::factory<unique_base_ptr(int)>::register_product<foo>();
     *          ans::factory<shared_base_ptr(int)>::register_product<foo>();
     *      }
     *  };
     *  
     *  struct bar : base
     *  {
     *      bar(int x) : base(x) {}
     *      int f() const { return x + 2; }
     *      static std::string identifier() { return "bar"; }
     *  
     *      void never_call_me()
     *      {
     *          ans::factory<base_ptr(int)>::register_product<bar>();
     *          ans::factory<unique_base_ptr(int)>::register_product<bar>();
     *          ans::factory<shared_base_ptr(int)>::register_product<bar>();
     *      }
     *  };
     *  
     *  BOOST_AUTO_TEST_CASE(t_factory)
     *  {
     *      auto &f = ans::factory<base_ptr(int)>::instance();
     *      auto p = f.make("foo")(0);
     *      auto q = f.make("bar")(0);
     *      BOOST_CHECK_EQUAL(p->f(), 1);
     *      BOOST_CHECK_EQUAL(q->f(), 2);
     *      delete p;
     *      delete q;
     *      BOOST_CHECK_EQUAL(ans::factory<unique_base_ptr(int)>::make("foo")(0)->f(), 1);
     *      BOOST_CHECK_EQUAL(ans::factory<unique_base_ptr(int)>::make("bar")(0)->f(), 2);
     *      BOOST_CHECK_EQUAL(ans::factory<shared_base_ptr(int)>::make("foo")(3)->f(), 4);
     *      BOOST_CHECK_EQUAL(ans::factory<shared_base_ptr(int)>::make("bar")(4)->f(), 6);
     *  }
     *  </code></pre>
     */
    template<class Signature, class Identifier>
    class factory : boost::noncopyable
    {
    private:
        /**
         *  make factory method signature by given signature
         */
        struct maker_signature
        {
            //typedef typename boost::function_types::result_type<Signature>::type base_type;
            //typedef boost::function_types::parameter_types<Signature> parameter_types;
            //typedef boost::shared_ptr<base_type> base_ptr;
            //typedef typename boost::mpl::push_front<parameter_types, base_ptr>::type composed_types;
            //typedef typename boost::function_types::function_type<composed_types>::type type;

            /// @todo check return type, must be pointer or smart pointer
            typedef Signature type;
        };

    public:
        typedef boost::function<typename maker_signature::type> maker_type;
        typedef typename maker_type::result_type result_type;
        typedef Identifier identifier_type;

    public:
        /**
         *  client may need to specialize this class template to give other
         *  identifier definition.
         */
        template<class Product>
        struct product_traits;

    public:
        static factory & instance();

        /// get factory methods by given id
        static const maker_type & make(const identifier_type &id);

        /// register product by given id and factory method
        static void register_product(const identifier_type &id, const maker_type &maker);

        /**
         *  Register by type.
         *  
         *  Product should have static member function 'identity' or specialize
         *  'product_traits'
         *  
         *  <b>This function template only need to be instantiate explicitly,
         *  and don't need to be called actually.</b>
         */
        template<class Product>
        static void register_product();

    private:
        /// make it private for singleton
        factory();

        /// expose construct to boost
        friend boost::serialization::detail::singleton_wrapper<factory>;

        void _register_product(const identifier_type &id, const maker_type &maker);

        /// get factory methods by given id, just for internal use
        const maker_type & operator [](const identifier_type &id) const;

    private:
        std::map<identifier_type, maker_type> m_makers;
    };
}