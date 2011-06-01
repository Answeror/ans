/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

shift << a << b << c;
equals
b = c; a = b;

TODO: use boost.proto impl.
--------------------------------------------------------------------------------
*/

namespace ans {

namespace shift_detail {

struct shift_head {};

template<class T>
struct shift_hold {
    T &data;
    shift_hold(T &t) : data(t) {}
};

template<class T>
inline shift_hold<T> operator <<(shift_head, T &t) {
    return shift_hold<T>(t);
}

template<class U, class T>
inline shift_hold<T> operator <<(shift_hold<U> lhs, T &t) {
    lhs.data = t;
    return shift_hold<T>(t);
}

} // shift_detail

//------------------------------------------------------------------------------

namespace {
    const shift_detail::shift_head shift;
}

} // ans
