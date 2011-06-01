#ifndef ANS_DIV_HPP
#define ANS_DIV_HPP

/*
@author: Answeror
@description: Safe division.
*/

#include <boost/optional.hpp>

namespace ans {

template<class T>
inline boost::optional<T> div(T lhs, T rhs) {
    if (rhs == 0) return boost::none;
    else return lhs / rhs;
}

}

#endif
