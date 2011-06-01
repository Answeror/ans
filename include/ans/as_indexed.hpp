#ifndef ANS_AS_INDEXED_HPP
#define ANS_AS_INDEXED_HPP

/*
@author: Answeror
@description:
Transform index to elem at this index.
Note target range is passed by value to support rvalue, so use
boost::iterator_range to wrap when use container rather than range.
*/

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace ans {

namespace range_detail {

template<class T>
struct as_index {
    typedef typename boost::range_reference<T>::type result_type;
    T t;
    explicit as_index(T t) : t(t) {}
    template<class Index>
    result_type operator ()(Index i) const { return t[i]; }
};

template<class R, class T>
struct as_index_range : boost::transform_range<as_index<T>, const R> {
private:
    typedef as_index<T> fn;
    typedef boost::transform_range<fn, const R> base;

public:
    as_index_range(const R &r, T t) : base(fn(t), r) {}
}; // as_index_range

template<class T>
struct as_index_holder : 
    boost::range_detail::holder<T>
{
    as_index_holder(T t) :
        boost::range_detail::holder<T>(t)
    {}
};

template<class InputRange, class T>
inline as_index_range<InputRange, T>
operator |(InputRange &r, const as_index_holder<T> &t) {
    return as_index_range<InputRange, T>(r, t.val);
}

template<class InputRange, class T>
inline as_index_range<InputRange, T>
operator |(const InputRange &r, const as_index_holder<T> &t) {
    return as_index_range<InputRange, T>(r, t.val);
}

} // range_detail

using range_detail::as_index_range;

namespace adaptors {

namespace {
    const boost::range_detail::forwarder<
        range_detail::as_index_holder
    > as_indexed;
}

} // adaptors

} // ans

#endif
