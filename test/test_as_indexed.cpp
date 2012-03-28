/*
--------------------------------------------------------------------------------
@author: answeror
@description: 
--------------------------------------------------------------------------------
*/

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
    #define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#include <vector>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <pstade/oven/initial_values.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/transformed.hpp>

#include <ans/as_indexed.hpp>
#include <ans/parenthesis_as_bracket.hpp>

std::vector<int> gen()
{
    std::vector<int> a = pstade::oven::initial_values(1,2,3,4,5);
    return a;
}

BOOST_AUTO_TEST_CASE(t_as_indexed)
{
    using namespace pstade::oven;
    int indices[] = {0, 1, 2};
    std::vector<int> a;
    a = indices | transformed(ans::make_parenthesis_as_bracket(boost::ref(gen()))) | copied;
    a = indices | ans::adaptors::as_indexed(boost::ref(gen())) | copied;
    a = indices | ans::adaptors::as_indexed(gen()) | copied;
    BOOST_REQUIRE(equals(indices | ans::adaptors::as_indexed(gen()), gen() | taken(3)));
}
