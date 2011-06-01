#ifndef ANS_SUBSCRIPED_HPP
#define ANS_SUBSCRIPED_HPP

/*
@author: Answeror
@description: To support vector of vector.
*/

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace ans {

namespace range_detail {

//template<class T, class Index>
//struct subscript {
//    typedef typename T::reference result_type;
//    
//    Index i;
//    
//    explicit subscript(Index i) : i(i) {}
//    result_type operator ()(T &t) const {
//        return t[i];
//    }
//};
//
//template<class T, class Index>
//struct subscript<const T, Index> {
//    typedef typename T::const_reference result_type;
//    
//    Index i;
//    
//    explicit subscript(Index i) : i(i) {}
//    result_type operator ()(const T &t) const {
//        return t[i];
//    }
//};

template<class T, class Index>
struct subscript {
    typedef typename boost::range_reference<T>::type result_type;
    
    Index i;
    
    explicit subscript(Index i) : i(i) {}
    result_type operator ()(T &t) const {
        return t[i];
    }
};

template<class R, class Index>
struct subscript_range : 
    boost::transform_range<
        subscript<
            // boost::range_value just return the value with const removed.
            typename boost::remove_reference<
                typename boost::range_reference<R>::type
            >::type,
            Index
        >, 
        R
    >
{
private:
    typedef subscript<
        typename boost::remove_reference<
            typename boost::range_reference<R>::type
        >::type,
        Index
    > sub;
    typedef boost::transform_range<sub, R> base;

public:
    subscript_range(R &r, Index i) : base(sub(i), r) {}
}; // subscript_range

template<class Index>
struct subscript_holder : 
    boost::range_detail::holder<Index>
{
    subscript_holder(Index index) :
        boost::range_detail::holder<Index>(index)
    {}
};

template<class InputRange, class Index>
inline subscript_range<InputRange, Index>
operator |(InputRange &r, const subscript_holder<Index> &i) {
    return subscript_range<InputRange, Index>(r, i.val);
}

template<class InputRange, class Index>
inline subscript_range<const InputRange, Index>
operator |(const InputRange &r, const subscript_holder<Index> &i) {
    return subscript_range<const InputRange, Index>(r, i.val);
}

} // range_detail

using range_detail::subscript_range;

namespace adaptors {

namespace {
    const boost::range_detail::forwarder<
        range_detail::subscript_holder
    > subscripted;
}

} // adaptors

} // ans

#endif
