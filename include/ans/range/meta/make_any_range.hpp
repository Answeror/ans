#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __MAKE_ANY_RANGE_HPP_20120328190441__
#define __MAKE_ANY_RANGE_HPP_20120328190441__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-28
 *  
 *  @section DESCRIPTION
 *  
 *  Convenient meta function to build `boost::any_range`.
 */

#include <boost/range/adaptor/type_erased.hpp>

#include <ans/type_traits/value_type.hpp>

namespace ans { namespace range
{
    namespace meta
    {
        /**
         *  Build `boost::any_range` by reference and traversal type.
         */
        template<class Reference, class Traversal>
        struct make_any_range
        {
            typedef boost::any_range<
                typename ans::value_type<Reference>::type,
                Traversal,
                Reference,
                std::ptrdiff_t
            > type;
        };
    }
}}

#endif // __MAKE_ANY_RANGE_HPP_20120328190441__
