#ifndef ANS_ASSERT_HPP
#define ANS_ASSERT_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

Assert followed by a exception throwing, for safty.
--------------------------------------------------------------------------------
*/

#include "check.hpp"
#include "warning.hpp"

#define ANS_ASSERT(condition) assert(condition); CHECK(std::logic_error, condition)

#ifdef ASSERT
    #pragma message WARN("ASSERT already defined in other place, so ANS_ASSERT won't be defined as ASSERT.")
#else
    #define ASSERT(condition) ANS_ASSERT(condition)
#endif

#endif
