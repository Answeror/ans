/*
--------------------------------------------------------------------------------
@author: answeror
@description: 
--------------------------------------------------------------------------------
*/

#define BOOST_TEST_MAIN

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <ans/pfo.hpp>

int foo(int a)
{
    return a;
}

double foo(double a)
{
    return a + 1;
}

PFO(foo)

BOOST_AUTO_TEST_CASE(t_pfo)
{
    BOOST_CHECK_EQUAL(foo_pfo(1), 1);
    BOOST_CHECK_EQUAL(foo_pfo(1.0), 2.0);
}