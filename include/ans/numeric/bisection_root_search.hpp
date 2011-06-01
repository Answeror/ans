#ifndef ANS_NUMERIC_BISECTION_ROOT_SEARCH_HPP
#define ANS_NUMERIC_BISECTION_ROOT_SEARCH_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 
--------------------------------------------------------------------------------
*/

template<class Fn, class Real>
Real bisection_root_search(Fn fn, Real a, Real b, Real eps) {
    assert(a < b && "Invalid range.");
    const Real fl = fn(a);
    const Real fr = fn(b);
    assert(fl * fr < 0 && "Root must bracketed for bisection.");
    
    const int iteration_limit = 40;
    Real xlow;
    Real dx;
    if (fl < 0) {
        xlow = a;
        dx = b - a;
    } else {
        xlow = b;
        dx = a - b;
    }
    for (int i = 0; i < iteration_limit; ++i) {
        Real xmid = xlow + (dx *= 0.5);
        Real fmid = fn(xmid);
        if (fmid <= 0) xlow = xmid;
        if (abs(dx) < eps || 0 == fmid) return xmid;
    }
    
    assert(false && "Too many bisections.");
    return 0;
}

#endif
