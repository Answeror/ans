#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __FWD_HPP_20120323194952__
#define __FWD_HPP_20120323194952__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-23
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/fusion/container/map/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace ans
{
    struct static_property_tree_tag;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_MAP_SIZE, typename T, void_)
    >
    class static_property_tree;
}

#endif // __FWD_HPP_20120323194952__
