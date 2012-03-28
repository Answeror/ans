#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __STATIC_PROPERTY_TREE_HPP_20120323165149__
#define __STATIC_PROPERTY_TREE_HPP_20120323165149__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-23
 *  
 *  @section DESCRIPTION
 *  
 *  Like boost::property_tree, but this is a more efficient static one.
 */

#include <boost/fusion/include/map.hpp>

#include "fwd.hpp"

namespace ans
{
    namespace bofu = boost::fusion;

    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, typename T)>
    class static_property_tree :
        public bofu::map<BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)>
    {
    public:
        typedef bofu::map<BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)> base_type;

    public:
        static_property_tree() : base_type() {}

        /**
         *  Construct from a fusion sequence.
         */
        template<class Sequence>
        static_property_tree(const Sequence &rhs) : base_type(rhs) {}

#include "detail/forward_ctor.hpp"
    };
}

#endif // __STATIC_PROPERTY_TREE_HPP_20120323165149__
