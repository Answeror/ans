#ifndef ANS_DEREFERENCE_HPP
#define ANS_DEREFERENCE_HPP

/*
<author>Answeror</author>
<create-time>2010-08-26</create-time>
<description>
Safer dereference for pointer, smart pointer, iterator(not support now, 
because of null iterator's definition).
</description>
*/

#include <boost/pointee.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/optional/optional_fwd.hpp>

#include "check.hpp"

namespace ans {

template<class T>
struct checked {
    static void check(const T &arg, const T &invalid) {
        ans::check<std::runtime_error>(
            arg != invalid,
            "Bad dereference."
        );
    }
};

template<class T>
struct unchecked {
    static void check(const T &arg) {}
};

namespace detail {

template<class T>
struct is_pointer : boost::is_pointer<T> {};

template<class T>
struct is_pointer<boost::shared_ptr<T> > : boost::mpl::true_ {};
/*
//@2010-12-11 added
template<class T>
struct is_pointer<boost::optional<T> > : boost::mpl::false_ {};
*/
} // detail

/*
// Use checked dereference default.
template<class T, template<class> class Policy = checked>
typename boost::pointee<T>::type dereference(const T &arg) {
    Policy<T>::check(arg);
    return *arg;
}
*/

template<class T, class U>
U dereference_impl(
    const T &arg,
    const T &invalid
) {
    checked<T>::check(arg, invalid);
    return *arg;
}

template<class T>
typename boost::pointee<T>::type & dereference(
    const T &arg,
    const T &invalid
) {
    return dereference_impl<T, typename boost::pointee<T>::type &>(arg, invalid);
}

template<class T>
typename boost::lazy_enable_if<
    detail::is_pointer<T>,
    boost::pointee<T>
>::type& dereference(const T &arg) {
    return dereference<T>(arg, T((typename boost::pointee<T>::type*)0));
}

/*
//@2010-12-11 added
template<class T>
T dereference(const boost::optional<T> &arg) {
    return dereference_impl<boost::optional<T>, T>(arg, boost::none);
}*/

} // ans

#endif
