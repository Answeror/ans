#ifndef ANS_SHARED_ACCESSOR_HPP
#define ANS_SHARED_ACCESSOR_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: Convert boost::shared_ptr to a functor that return obj ref.
--------------------------------------------------------------------------------
*/

#include <boost/shared_ptr.hpp>

namespace ans {

template<class T>
struct shared_accessor {
    typedef boost::shared_ptr<T> pointer_type;
    typedef T &result_type;
    
    const pointer_type p;
    
    shared_accessor(const pointer_type &p) : p(p) {}
    
    result_type operator ()() const { return *p; }
};

template<class T>
shared_accessor<T> make_shared_accessor(
    const boost::shared_ptr<T> &p
) {
    return shared_accessor<T>(p);
}

} // ans

#endif
