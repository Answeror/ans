#ifndef ANS_STATIC_ASSERT_HPP
#define ANS_STATIC_ASSERT_HPP

/*
<author>Answeror</author>
<create-time>2010-08-23</create-time>
*/

#include <boost/static_assert.hpp>

#ifndef static_assert
    #define static_assert(a) BOOST_STATIC_ASSERT(a)
#endif

#endif
