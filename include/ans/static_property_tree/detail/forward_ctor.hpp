#ifndef BOOST_PP_IS_ITERATING

#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __FORWARD_CTOR_HPP_20120323194338__
#define __FORWARD_CTOR_HPP_20120323194338__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-23
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    "detail/forward_ctor.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

#if N == 1
    explicit
#endif
    static_property_map(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& _))
        : base_type(BOOST_PP_ENUM_PARAMS(N, _)) {}

#undef N

#endif // __FORWARD_CTOR_HPP_20120323194338__

#endif // defined(BOOST_PP_IS_ITERATING)