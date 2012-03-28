/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-27
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "alpha_pimpl/someclass.hpp"

BOOST_AUTO_TEST_CASE(t_alpha_pimpl)
{
    someclass something;
    BOOST_REQUIRE_EQUAL(-42, something.foo());
}