#ifndef ANS_NUMERIC_TRAPEZOIAL_HPP
#define ANS_NUMERIC_TRAPEZOIAL_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 
--------------------------------------------------------------------------------
*/

#include "ans/check.hpp"

namespace ans { namespace numeric {

template<class Real, class Fn>
struct trapezoidal {
    typedef Real real_type;
    
    Fn fn;
    real_type a, b, s;
    int n;
    
    //--------------------------------------------------------------------------
    
    trapezoidal(const Fn &fn, real_type a, real_type b) : 
        fn(fn), a(a), b(b), n(0)
    {}
    
    real_type next() {
        ++n;
        CHECK(std::runtime_error, n < 32 && "Too many iterations.");
        if (1 == n) return s = real_type(0.5) * (b - a) * (fn(a) + fn(b));
        const int pn = 1 << (n - 2); // added point count
        const real_type step = (b - a) / pn; // space between point to be added
        real_type x = a + real_type(0.5) * step;
        real_type sum = 0;
        for (int i = 0; i < pn; ++i) {
            sum += fn(x);
            x += step;
        }
        return s = real_type(0.5) * (s + step * sum);
    }
    
    int iteration() const { return n; }
    
    real_type result() const { return s; }
    
    static int sample(int n) { return 2 + (n < 2 ? 0 : ((1 << (n - 1)) - 1)); }
}; // trapezoidal

} // numeric
} // ans

#endif // ANS_NUMERIC_TRAPEZOIAL_HPP
