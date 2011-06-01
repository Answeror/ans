/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 
--------------------------------------------------------------------------------
*/

#include <cmath>

namespace ans {

template<class T, class U>
inline T sign(T value, U sign_) {
    return sign_ > 0 ? abs(value) : -abs(value);
}

} // ans
