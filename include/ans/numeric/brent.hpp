/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 
--------------------------------------------------------------------------------
*/

#include <cmath>
#include <limits>

#include "../check.hpp"
#include "../shift.hpp"
#include "utility.hpp"

namespace ans { namespace numeric {

template<class Real>
struct brent {
    Real xmin, fmin;
    
    template<class Fn>
    brent(Fn fn, Real ax, Real bx, Real cx, Real tol = 3e-8) {
        const int ITMAX = 100;
        const Real CGOLD = 0.3819660;
        const Real ZEPS = std::numeric_limits<Real>::epsilon() * 1e-3;
        
        Real d = 0;
        Real e = 0; // distance moved on the step before last
        Real a = std::min(ax, cx);
        Real b = std::max(ax, cx);
        Real x, w, v, fx, fw, fv;
        x = w = v = bx;
        fx = fw = fv = fn(bx);
        for (int it = 0; it < ITMAX; ++it) {
            Real xm = 0.5 * (a + b);
            Real tol_half = tol * abs(x) + ZEPS;
            Real tol = 2 * tol_half;
            // test for done
            if (abs(x - xm) <= tol - 0.5 * (b - a)) {
                fmin = fx;
                xmin = x;
                return;
            }
            // use x, w, v to make parabolic fix
            // check if need to re-eval
            if (abs(e) > tol_half) {
                Real r = (x - w) * (fx - fv);
                Real q = (x - v) * (fx - fw);
                Real p = (x - v) * q - (x - w) * r;
                q = 2 * (q - r);
                if (q > 0) p = -p;
                q = abs(q);
                Real eprev = e;
                e = d;
                
                // the acceptability of the parabolic fit
                if (
                    // imply a movement from the best current value x that is
                    // less than half the movement of the step before last
                    abs(p) >= abs(0.5 * q * eprev) ||
                    // out of bracket
                    p <= q * (a - x) || p >= q * (b - x)
                ) {
                    // take the golden section step into the larget of the two
                    // segments
                    d = CGOLD * (e = (x >= xm ? a - x : b - x));
                } else {
                    d = p / q;
                    Real u = x + d;
                    // step too large, make it small
                    if (u - a < tol || b - u < tol) {
                        d = sign(tol_half, xm - x);
                    }
                }
            } else {
                d = CGOLD * (e = (x >= xm ? a - x : b - x)); // TODO: refactor
            }
            
            // next pos, check if d too small
            Real u = (abs(d) >= tol_half ? x + d : x + sign(tol_half, d));
            // this is the one function evaluation pre iteration
            Real fu = fn(u);
            if (fu <= fx) {
                (u >= x ? a : b) = x;
                shift << v << w << x << u;
                shift << fv << fw << fx << fu;
            } else {
                (u < x ? a : b) = u;
                if (fu <= fw || w == x) {
                    shift << v << w << u;
                    shift << fv << fw << fu;
                } else if (fu <= fv || v == x || v == w) {
                    v = u;
                    fv = fu;
                }
            }
        }
        CHECK(std::runtime_error, false && "Too many iterations in brent.");
    }
};

} // numeric
} // ans
