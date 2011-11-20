#include <boost/test/unit_test.hpp>

#include <iostream>

#include <ans/b4main.hpp>

int & a()
{
    static int _a = 0;
    return _a;
}
void inc()
{
    ++a();
    std::cout << "a:" << a() << std::endl;
}

//namespace
//{
//    const ans::b4main<&inc> _;
//}

// typedef ans::b4main<&inc> _;
struct _ : ans::b4main<&inc> { _() {} };



BOOST_AUTO_TEST_CASE(t_b4main)
{
    //BOOST_CHECK_EQUAL(a(), 1);
    //BOOST_CHECK_EQUAL(incb4main::done, true);
}