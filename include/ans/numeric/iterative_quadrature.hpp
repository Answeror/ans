#ifndef ANS_NUMERIC_ITERATIVE_QUADRATURE_HPP
#define ANS_NUMERIC_ITERATIVE_QUADRATURE_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: NR P164
--------------------------------------------------------------------------------
*/

#include <cmath>

#include "ans/check.hpp"

namespace ans { namespace numeric {

struct iterative_quadrature {
    int m_least_iteration;
    
    template<class QuadratureMethod>
    iterative_quadrature(
        QuadratureMethod &q, 
        int iteration_min = 5, 
        typename QuadratureMethod::real_type eps = 1e-8
    ) : 
        m_least_iteration(0)
    {
        typedef typename QuadratureMethod::real_type real_type;
        const int iteration_limit = 20;
        real_type prev = 0;
        for (int i = 0; i < iteration_limit; ++i) {
            const real_type now = q.next();
            if (i) {
                if (
                    abs(now - prev) < eps * abs(prev) || 
                    0 == now && 0 == prev
                ) {
                    // avoid spurious early convergence.
                    if (i >= iteration_min) return;
                } else {
                    m_least_iteration = i + 1;
                }
            }
            prev = now;
        }
        CHECK(std::runtime_error, "Too many steps in iterative_quadrature.");
    }
    
    int least_iteration() const { return m_least_iteration; }
};

} // numeric
} // ans

#endif // ANS_NUMERIC_ITERATIVE_QUADRATURE_HPP
