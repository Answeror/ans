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

    template<class Data>
    template<class Dummy>
    unique<Data>::unique(detail::use_default_ctor<Dummy>) :
        m(new data_type()) {}

    template<class Data>
    template<class A1>
    unique<Data>::unique(A1 &&a1) :
        m(new data_type(
            std::forward<A1>(a1)
            )) {}
 
    template<class Data>
    template<class A1, class A2>
    unique<Data>::unique(A1 &&a1, A2 &&a2) :
        m(new data_type(
            std::forward<A1>(a1),
            std::forward<A2>(a2)
            )) {}
     
    template<class Data>
    unique<Data>::~unique() {}
     
    template<class Data>
    inline typename const unique<Data>::data_type*
        unique<Data>::operator->() const
    {
        return m.get();
    }

    template<class Data>
    inline typename unique<Data>::data_type*
        unique<Data>::operator->()
    {
        return m.get();
    }

    template<class Data>
    inline typename const unique<Data>::data_type&
        unique<Data>::operator*() const
    {
        return *m.get();
    }

    template<class Data>
    inline typename unique<Data>::data_type&
        unique<Data>::operator*()
    {
        return const_cast<data_type&>(
            *boost::implicit_cast<const this_type&>(*this));
    }
}
}
}

#endif // ANS_ALPHA_PIMPL_DECLARE_INCLUDED

#endif // __PIMPL_IMPL_HPP_2011122504415__
