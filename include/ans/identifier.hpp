#if !defined(__IDENTIFIER_HPP_2011120200408__)
#define __IDENTIFIER_HPP_2011120200408__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-02
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace ans
{
    namespace mpl = boost::mpl;

    /**
     *  A trait function to extract class identifier.
     *  
     *  Client need to either provide a static method named identifier or
     *  specialize this method.
     */
    template<class T>
    inline std::string identifier()
    {
        return T::identifier();
    }

    namespace identifier_detail
    {
        struct has_identifier_impl
        {
            typedef char (&yes)[1];
            typedef char (&no)[2];

            template <typename T> static yes test(decltype(identifier<T>())*) ;
            template <typename T> static no test(...);
        };
    }

    /**
     *  Use SFINAE to test whether T meet default identifer() definition or has
     *  a specialization.
     */
    template <typename T>
    struct has_identifier : mpl::bool_<
        sizeof(identifier_detail::has_identifier_impl::test<T>(0))
            == sizeof(identifier_detail::has_identifier_impl::yes)
        > {};

    template<class T>
    inline std::string identified_after(const std::string &s)
    {
        return identifier<T>() + "." + s;
    }

    //namespace identified_after_detail
    //{
    //    struct dot
    //    {
    //        std::string operator ()() const { return "."; }
    //    };
    //}

    /**
     *  This class is used to make identifier cascade.
     *  
     *  Derived class should provide static method do_identifier, this method
     *  could be public or protected.
     *  
     *  This class should be derived publicly. It can be derived by normal class
     *  or identifier_impl.
     *  
     *  @param Sep separator, default is "."
     */
    //template<class Derived, class Base, class Sep = identified_after_detail::dot>
    //class identified_after
    //{
    //private:
    //    typedef typename boost::remove_const<
    //        typename boost::remove_reference<
    //            decltype(Sep()())
    //            >::type
    //        >::type value_type;

    //public:
    //    static const value_type& identifier()
    //    {
    //        struct accessor : Derived { using Derived::do_identifier; };
    //        static value_type s = ::ans::identifier<Base>() + Sep()() + accessor::do_identifier();
    //        return s;
    //    }
    //};
}

#endif // __IDENTIFIER_HPP_2011120200408__
