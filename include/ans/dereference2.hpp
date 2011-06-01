#ifndef ANS_DEREFERENCE_2_HPP
#define ANS_DEREFERENCE_2_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: Just a extension for dereference.hpp.
--------------------------------------------------------------------------------
*/

#include "dereference.hpp"

namespace ans { namespace functional {

struct dereference {
    template<class Sig>
    struct result;
    
    template<class T>
    struct result<dereference(T)> {
        typedef typename boost::pointee<T>::type &type;
    };
    
    template<class T>
    typename result<dereference(T)>::type operator ()(T t) const {
        return *t;
    }
}; // dereference

} // functional
} // ans

#endif
