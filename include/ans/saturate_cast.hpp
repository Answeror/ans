#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __SATURATE_CAST_HPP_20120329153222__
#define __SATURATE_CAST_HPP_20120329153222__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2012-03-29
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <limits>

#include <boost/numeric/conversion/cast.hpp>
//#include <boost/assert.hpp>

namespace ans
{
    /**
     *  Used to do color cast, from real type to unsigned char.
     */
    template<typename Target, typename Source>
    Target saturate_cast(Source src) {
        try {
            return boost::numeric_cast<Target>(src);
        }
        catch (const boost::numeric::negative_overflow &) {
            //BOOST_ASSERT(false);
            return std::numeric_limits<Target>::min();
        }
        catch (const boost::numeric::positive_overflow &) {
            //BOOST_ASSERT(false);
            return std::numeric_limits<Target>::max();
        }
    }
}

#endif // __SATURATE_CAST_HPP_20120329153222__