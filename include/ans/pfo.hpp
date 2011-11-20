#ifndef ANS_PFO_HPP
#define ANS_PFO_HPP

#include <boost/utility/declval.hpp>

#define PFO(fn)\
    namespace\
    {\
        struct fn##_pf\
        {\
            template<class A1>\
            decltype(fn(boost::declval<A1>()))\
                operator ()(A1 &&a1) const\
            {\
                return fn(std::forward<A1>(a1));\
            }\
\
            template<class A1, class A2>\
            decltype(fn(boost::declval<A1>(), boost::declval<A2>()))\
                operator ()(A1 &&a1, A2 &&a2) const\
            {\
                return fn(std::forward<A1>(a1), std::forward<A2>(a2));\
            }\
        };\
        const fn##_pf fn##_pfo;\
    }

#endif
