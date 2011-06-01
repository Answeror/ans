#ifndef ANS_CONSTED_HPP
#define ANS_CONSTED_HPP

/*
@author: Answeror
@description:
Make reference const. Used to support indirected.
Only support lvalue range!
*/

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_const.hpp>

namespace ans {

namespace range_detail {

template<class T>
struct constant {
    typedef typename boost::add_const<
        typename boost::remove_reference<T>::type
    >::type &result_type;
    result_type operator ()(result_type t) const { return t; }
};

template<class R>
struct const_range : 
    boost::transform_range<
        constant<typename boost::range_reference<R>::type>, 
        R
    >
{
private:
    typedef constant<typename boost::range_reference<R>::type> fn;
    typedef boost::transform_range<fn, R> base;

public:
    const_range(R &r) : base(fn(), r) {}
}; // const_range

struct const_forwarder {};

template<class InputRange>
inline const_range<InputRange>
operator |(InputRange &r, const_forwarder) {
    return const_range<InputRange>(r);
}

template<class InputRange>
inline const_range<const InputRange>
operator |(const InputRange &r, const_forwarder) {
    return const_range<const InputRange>(r);
}

} // range_detail

using range_detail::const_range;

namespace adaptors {

namespace {
    const range_detail::const_forwarder consted;
}

} // adaptors

} // ans

#endif
