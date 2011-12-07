#if !defined(__PIMPL_HPP_20111207130446__)
#define __PIMPL_HPP_20111207130446__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-07
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#define ANS_PIMPL_DECLARE_INCLUDED

#include <boost/implicit_cast.hpp>

#include <memory> // unique_ptr

namespace ans { namespace beta { namespace pimpl {

    /**
     *  Use std::unique_ptr to hold data.
     *  
     *  @param Method must derived from host class.
     */
    template<class Data, class Method = void>
    class unique;

    /**
     *  No data required.
     *  
     *  @param Method must derived from host class.
     */
    template<class Method>
    class stateless;

    namespace detail
    {
        template<class Method>
        struct method_policy;

        /**
         *  Method class access policy.
         *  
         *  Not method is a static member, so it can be used in the constructor
         *  of the host class if the target method of the Method class does not
         *  use host member.
         */
        template<class Method>
        struct method_policy
        {
            typedef Method method_type;

            template<class Host>
            static const method_type& method(const Host *p);

            template<class Host>
            static method_type& method(Host *p);

            template<class Host>
            static const method_type& method(const Host &p);

            template<class Host>
            static method_type& method(Host &p);
        };

        /// no method provided
        template<>
        struct method_policy<void> {};

        template<class>
        struct use_default_ctor {};
    }

    typedef detail::use_default_ctor<void> use_default_ctor;

    template<class Method>
    class stateless : public detail::method_policy<Method>
    {
    private:
        typedef detail::use_default_ctor<void> use_default_ctor;
        typedef stateless this_type;

    public:
        stateless();

        template<class Dummy>
        stateless(detail::use_default_ctor<Dummy>);
    };
     
    template<class Data, class Method>
    class unique : public detail::method_policy<Method>
    {
    protected:
        typedef detail::use_default_ctor<void> use_default_ctor;
        typedef Data data_type;

    private:
        typedef unique this_type;

    public:
        template<class Dummy>
        unique(detail::use_default_ctor<Dummy>);

        template<class A1>
        unique(A1 &&a1);

        template<class A1, class A2>
        unique(A1 &&a1, A2 &&a2);

        ~unique();

        const data_type& data() const;

        data_type& data();

        //const data_type* operator->() const;

        //data_type* operator->();

        //const data_type& operator*() const;

        //data_type& operator*();

    private:
        std::unique_ptr<data_type> m;
    };

}
}
}

#endif // __PIMPL_HPP_20111207130446__
