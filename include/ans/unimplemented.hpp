#ifndef ANS_UNIMPLEMENTED_HPP
#define ANS_UNIMPLEMENTED_HPP

/*
@author: Answeror
@description: A simple assert to be placed in unimplemented funcion.
*/

#include <cassert>

namespace ans {

inline void unimplemented() {
    assert(false && "unimplemented");
}

} // ans

#endif
