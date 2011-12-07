#if !defined(__PIMPL_IMPL_HPP_20111207133048__)
#define __PIMPL_IMPL_HPP_20111207133048__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-07
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

/// prevent useless include
#ifdef ANS_PIMPL_DECLARE_INCLUDED

#include <boost/implicit_cast.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace ans { namespace beta { namespace pimpl {

    namespace detail
    {
        /// provide a indirection to feed static_assert
        template<class To, class From>
        inline To cast(From &&from)
        {
            return static_cast<To>(from);
        }

        template<class Method>
        template<class Host>
        inline const typename method_policy<Method>::method_type&
            method_policy<Method>::method(const Host &p)
        {
            static_assert(boost::is_base_of<Host, method_type>::value,
                "Host must be base of Method.");
            //return static_cast<const method_type&>(p);
            return cast<const method_type&>(p);
        }

        template<class Method>
        template<class Host>
        inline typename method_policy<Method>::method_type&
            method_policy<Method>::method(Host &p)
        {
            return const_cast<method_type&>(
                method(boost::implicit_cast<const Host&>(p)));
        }

        template<class Method>
        template<class Host>
        inline const typename method_policy<Method>::method_type&
            method_policy<Method>::method(const Host *p)
        {
            return method(*p);
        }

        template<class Method>
        template<class Host>
        inline typename method_policy<Method>::method_type&
            method_policy<Method>::method(Host *p)
        {
            return method(*p);
        }
    }

    template<class Method>
    stateless<Method>::stateless() {}

    template<class Method>
    template<class Dummy>
    stateless<Method>::stateless(detail::use_default_ctor<Dummy>) {}

    template<class Data, class Method>
    template<class Dummy>
    unique<Data, Method>::unique(detail::use_default_ctor<Dummy>) :
        m(new data_type()) {}

    template<class Data, class Method>
    template<class A1>
    unique<Data, Method>::unique(A1 &&a1) :
        m(new data_type(
            std::forward<A1>(a1)
            )) {}
 
    template<class Data, class Method>
    template<class A1, class A2>
    unique<Data, Method>::unique(A1 &&a1, A2 &&a2) :
        m(new data_type(
            std::forward<A1>(a1),
            std::forward<A2>(a2)
            )) {}
     
    template<class Data, class Method>
    unique<Data, Method>::~unique() {}
     
    //template<class Data, class Method>
    //inline typename const unique<Data, Method>::data_type*
    //    unique<Data, Method>::operator->() const
    //{
    //    return &(*this);
    //}

    //template<class Data, class Method>
    //inline typename unique<Data, Method>::data_type*
    //    unique<Data, Method>::operator->()
    //{
    //    return &(*this);
    //}

    //template<class Data, class Method>
    //inline typename const unique<Data, Method>::data_type&
    //    unique<Data, Method>::operator*() const
    //{
    //    return *m.get();
    //}

    //template<class Data, class Method>
    //inline typename unique<Data, Method>::data_type&
    //    unique<Data, Method>::operator*()
    //{
    //    return const_cast<data_type&>(
    //        boost::implicit_cast<const this_type&>(*this)());
    //}

    template<class Data, class Method>
    inline typename const unique<Data, Method>::data_type&
        unique<Data, Method>::data() const
    {
        return *m.get();
    }

    template<class Data, class Method>
    inline typename unique<Data, Method>::data_type&
        unique<Data, Method>::data()
    {
        return const_cast<data_type&>(
            boost::implicit_cast<const this_type&>(*this)());
    }
}
}
}

#endif // ANS_PIMPL_DECLARE_INCLUDED

#endif // __PIMPL_IMPL_HPP_20111207133048__
