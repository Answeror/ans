#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __DEFINE_NESTED_TRAITS_HPP_20120328124610__
#define __DEFINE_NESTED_TRAITS_HPP_20120328124610__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-28
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#define ANS_DEFINE_NESTED_TRAITS(host, traits, otherwise)\
    template<class host>\
    struct traits\
    {\
        template<class T>\
        static typename T::traits select(const typename T::traits*);\
        template<class T>\
        static otherwise select(...);\
        typedef decltype(select<host>(0)) type;\
    };

#endif // __DEFINE_NESTED_TRAITS_HPP_20120328124610__
