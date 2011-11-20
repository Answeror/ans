/*
--------------------------------------------------------------------------------
@author: answeror
@description: 
--------------------------------------------------------------------------------
*/

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
    #define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#include <boost/test/unit_test.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>

struct foo
{
    int operator ()()
    {
        return 0;
    }

    double operator ()() const
    {
        return 1;
    }
};

BOOST_AUTO_TEST_CASE(t_decltype)
{
    foo f;
    const foo cf;
    static_assert(boost::is_same<boost::result_of<foo()>::type, int>::value, "a");
    static_assert(boost::is_same<boost::result_of<const foo()>::type, double>::value, "b");
}

