#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __PIMPL_HPP_2011122503156__
#define __PIMPL_HPP_2011122503156__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-25
 *  
 *  @section DESCRIPTION
 *  
 *  This is a upgrade version based on ans::beta::pimpl, seperated data and
 *  method to two module.
 *  Now "data" and "method" can be used separately.
 *  
 *  @note
 *  
 *  Use `boost::scoped_ptr` instead of `std::unique_ptr` to work with gccxml 0.9
 *  which use GCC 4.2 internally and does not support 0x.
 *  
 *  BOOST_NO_RVALUE_REFERENCES is also used to make gccxml work.
 */

#define ANS_ALPHA_PIMPL_DECLARE_INCLUDED

//#include <memory> // unique_ptr
#include <boost/config.hpp> // detect rvalue support
#include <boost/scoped_ptr.hpp>

namespace ans { namespace alpha { namespace pimpl {

    /**
     *  Use std::unique_ptr to hold data.
     *  
     *  @param Method must derived from host class.
     */
    template<class Data>
    class unique;

    namespace detail
    {
        /**
         *  Dummy is just to make this class dependent on template argument.
         */
        template<class Dummy>
        struct use_default_ctor {};
    }

    typedef detail::use_default_ctor<void> use_default_ctor;

    template<class Data>
    class unique
    {
    protected:
        //typedef detail::use_default_ctor<void> use_default_ctor;
        typedef Data data_type;

    private:
        typedef unique this_type;

    public:
        template<class Dummy>
        unique(detail::use_default_ctor<Dummy>);

#ifdef BOOST_NO_RVALUE_REFERENCES
        template<class A1>
        unique(A1 &a1);

        template<class A1, class A2>
        unique(A1 &a1, A2 &a2);
#else
        template<class A1>
        unique(A1 &&a1);

        template<class A1, class A2>
        unique(A1 &&a1, A2 &&a2);
#endif

        ~unique();

        const data_type* operator->() const;

        data_type* operator->();

        const data_type& operator*() const;

        data_type& operator*();

    private:
        //std::unique_ptr<data_type> m;
        boost::scoped_ptr<data_type> m;
    };
}
}
}

#endif // __PIMPL_HPP_2011122503156__
