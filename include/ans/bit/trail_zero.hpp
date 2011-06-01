#ifndef ANS_BIT_TRAIL_ZERO_HPP
#define ANS_BIT_TRAIL_ZERO_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description:

Find the number of trailing zeros in 32-bit v.
From http://www.matrix67.com/blog/archives/3985
--------------------------------------------------------------------------------
*/

#include <cstddef> // size_t

namespace ans { namespace bit {

inline size_t trail_zero(unsigned int v) {
    static const size_t MultiplyDeBruijnBitPosition[32] =
    {
      0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
      31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    return MultiplyDeBruijnBitPosition[((unsigned int)((int(v) & -int(v)) * 0x077CB531U)) >> 27];
}

} // ans
} // bit

#endif
