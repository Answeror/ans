#ifndef ANS_NUMERIC_BRACKET_HPP
#define ANS_NUMERIC_BRACKET_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

expand_bracket may fail, e.g. y=x^2-1, a=4, b=5.
--------------------------------------------------------------------------------
*/

#include <cmath> // abs
#include <cassert>
#include <utility> // pair, make_pair

#include <boost/static_assert.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>  
#include <boost/concept_check.hpp>

namespace ans { namespace numeric {

namespace bracket_detail {

template<class Fn, class Real>
void common_check(Fn fn, Real a, Real b) {
    BOOST_STATIC_ASSERT((boost::is_same<Real, BOOST_TYPEOF(fn(a))>::value));
    assert(a < b && "Invalid range.");
}

}

// Expand a range to a bracket, may fail.
template<class Fn, class Real>
bool expand_bracket(Fn fn, Real &a, Real &b) {
    bracket_detail::common_check(fn, a, b);
    
    const int try_count = 50;
    const Real factor = 1.6;
    Real fl = fn(a);
    Real fr = fn(b);
    for (int i = 0; i < try_count; ++i) {
        if (fl * fr < 0) return true;
        if (abs(fl) < abs(fr)) fl = fn(a += factor * (a - b));
        else fr = fn(b += factor * (b - a));
    }
    return false;
}

// Sub divide a bracket into n segments and return segments which are remain
// bracket.
template<class Fn, class Real, class OutputIterator>
void divide_bracket(Fn fn, Real a, Real b, int n, OutputIterator out) {
    bracket_detail::common_check(fn, a, b);
    assert(n > 0 && "Segment count must > 0.");
    BOOST_CONCEPT_ASSERT((boost::OutputIterator<OutputIterator, std::pair<Real, Real> >));
    
    Real dx = (b - a) / n;
    Real x = a;
    Real fprev = fn(x);
    for (int i = 0; i < n; ++i) {
        const Real fnow = fn(x += dx);
        if (fprev * fnow <= 0) {
            *out++ = std::make_pair(x - dx, x);
        }
        fprev = fnow;
    }
}

} // numeric
} // ans

#endif
