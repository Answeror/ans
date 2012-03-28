#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __VALUE_TYPE_HPP_20120324153646__
#define __VALUE_TYPE_HPP_20120324153646__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-24
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace ans
{
    namespace type_traits
    {
        template<class T>
        struct value_type
        {
            typedef typename boost::remove_const<
                typename boost::remove_reference<T>::type
            >::type type;
        };
    }

    namespace
    {
        using type_traits::value_type;
    }
}

#endif // __VALUE_TYPE_HPP_20120324153646__
