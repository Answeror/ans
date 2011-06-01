#ifndef ANS_DEL_GUARD_HPP
#define ANS_DEL_GUARD_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description:
--------------------------------------------------------------------------------
*/

#include "del.hpp"
#include "guard.hpp"

namespace ans {

template<class T>
inline guard_impl<del<T> > make_del_guard(T *p)
{
    return make_guard(del<T>(p));
}

} // ans

#endif
