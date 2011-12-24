#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __PIMPL_IMPL_HPP_2011122504415__
#define __PIMPL_IMPL_HPP_2011122504415__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-25
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

/// prevent useless include
#ifdef ANS_ALPHA_PIMPL_DECLARE_INCLUDED

#include <boost/implicit_cast.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace ans { namespace alpha { namespace pimpl {

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
     
    template<class Data, class Method>
    inline typename const unique<Data, Method>::data_type*
        unique<Data, Method>::operator->() const
    {
        return &(*this);
    }

    template<class Data, class Method>
    inline typename unique<Data, Method>::data_type*
        unique<Data, Method>::operator->()
    {
        return &(*this);
    }

    template<class Data, class Method>
    inline typename const unique<Data, Method>::data_type&
        unique<Data, Method>::operator*() const
    {
        return *m.get();
    }

    template<class Data, class Method>
    inline typename unique<Data, Method>::data_type&
        unique<Data, Method>::operator*()
    {
        return const_cast<data_type&>(
            boost::implicit_cast<const this_type&>(*this)());
    }
}
}
}

#endif // ANS_ALPHA_PIMPL_DECLARE_INCLUDED

#endif // __PIMPL_IMPL_HPP_2011122504415__
