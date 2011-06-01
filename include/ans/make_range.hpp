#ifndef ANS_MAKE_RANGE_HPP
#define ANS_MAKE_RANGE_HPP

/*
<author>Answeror</author>
<date>2010-06-28</date>
*/

#include <boost/range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/indirect_iterator.hpp>

namespace ans {

namespace detail {

template<class T>
struct iterator_tuple;

template<class T0>
struct iterator_tuple<boost::tuple<T0> > {
    typedef boost::tuple<
        typename boost::range_iterator<T0>::type
    > type;
};

template<class T0, class T1>
struct iterator_tuple<boost::tuple<T0, T1> > {
    typedef boost::tuple<
        typename boost::range_iterator<T0>::type,
        typename boost::range_iterator<T1>::type
    > type;
};

template<class T0, class T1, class T2>
struct iterator_tuple<boost::tuple<T0, T1, T2> > {
    typedef boost::tuple<
        typename boost::range_iterator<T0>::type,
        typename boost::range_iterator<T1>::type,
        typename boost::range_iterator<T2>::type
    > type;
};

template<class T0>
typename iterator_tuple<
    boost::tuple<T0>
>::type make_begin_iterator_tuple(
    const boost::tuple<T0> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t))
    );
}

template<class T0>
typename iterator_tuple<
    boost::tuple<T0>
>::type make_end_iterator_tuple(
    const boost::tuple<T0> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t))
    );
}

template<class T0, class T1>
typename iterator_tuple<
    boost::tuple<T0, T1>
>::type make_begin_iterator_tuple(
    const boost::tuple<T0, T1> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t)),
        boost::begin(boost::get<1>(t))
    );
}

template<class T0, class T1>
typename iterator_tuple<
    boost::tuple<T0, T1>
>::type make_end_iterator_tuple(
    const boost::tuple<T0, T1> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t)),
        boost::end(boost::get<1>(t))
    );
}

template<class T0, class T1, class T2>
typename iterator_tuple<
    boost::tuple<T0, T1, T2>
>::type make_begin_iterator_tuple(
    const boost::tuple<T0, T1, T2> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t)),
        boost::begin(boost::get<1>(t)),
        boost::begin(boost::get<2>(t))
    );
}

template<class T0, class T1, class T2>
typename iterator_tuple<
    boost::tuple<T0, T1, T2>
>::type make_end_iterator_tuple(
    const boost::tuple<T0, T1, T2> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t)),
        boost::end(boost::get<1>(t)),
        boost::end(boost::get<2>(t))
    );
}

/*
// wrong ones... even use disable_if and boost::tuples::null_type
template<class T0>
boost::tuple<
    typename boost::range_iterator<T0>::type
> make_begin_iterator_tuple(
    const boost::tuple<T0, boost::tuples::null_type, boost::tuples::null_type> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t))
    );
}

template<class T0>
boost::tuple<
    typename boost::range_iterator<T0>::type
> make_end_iterator_tuple(
    const boost::tuple<T0, boost::tuples::null_type, boost::tuples::null_type> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t))
    );
}

template<class T0, class T1>
boost::tuple<
    typename boost::range_iterator<T0>::type,
    typename boost::range_iterator<T1>::type
> make_begin_iterator_tuple(
    const boost::tuple<T0, T1, boost::tuples::null_type> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t)),
        boost::begin(boost::get<1>(t))
    );
}

template<class T0, class T1>
boost::tuple<
    typename boost::range_iterator<T0>::type,
    typename boost::range_iterator<T1>::type
> make_end_iterator_tuple(
    const boost::tuple<T0, T1, boost::tuples::null_type> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t)),
        boost::end(boost::get<1>(t))
    );
}

template<class T0, class T1, class T2>
boost::tuple<
    typename boost::range_iterator<T0>::type,
    typename boost::range_iterator<T1>::type,
    typename boost::range_iterator<T2>::type
> make_begin_iterator_tuple(
    const boost::tuple<T0, T1, T2> &t
) {
    return boost::make_tuple(
        boost::begin(boost::get<0>(t)),
        boost::begin(boost::get<1>(t)),
        boost::begin(boost::get<2>(t))
    );
}

template<class T0, class T1, class T2>
boost::tuple<
    typename boost::range_iterator<T0>::type,
    typename boost::range_iterator<T1>::type,
    typename boost::range_iterator<T2>::type
> make_end_iterator_tuple(
    const boost::tuple<T0, T1, T2> &t
) {
    return boost::make_tuple(
        boost::end(boost::get<0>(t)),
        boost::end(boost::get<1>(t)),
        boost::end(boost::get<2>(t))
    );
}
*/

} // detail

// The Forwarding Problem: Arguments
// see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2002/n1385.htm
//
// 2010-06-29
//
// use Const + Non-const reference method
// note, only const reference approach will fail(
//     "no matching function for call to"
// )on following code:
//
// typedef pair<int, int> elem;
// vector<elem> v;
// te::make_transform_range(
//     v, boost::bind(&elem::first, _1)
// );
//
// must use:
// te::make_transform_range(
//     boost::make_iterator_range(v), boost::bind(&elem::first, _1)
// );

template<class Range, class UnaryFunc>
boost::iterator_range<boost::transform_iterator<
    UnaryFunc, typename boost::range_iterator<Range>::type
> > make_transform_range(
    Range &range,
    const UnaryFunc &func
) {
    return boost::make_iterator_range(
        boost::make_transform_iterator(
            boost::begin(range), func
        ),
        boost::make_transform_iterator(
            boost::end(range), func
        )
    );
}

template<class Range, class UnaryFunc>
boost::iterator_range<boost::transform_iterator<
    // 2010-07-29
    // 如果这样写对于const容器就会有问题, 而对于iterator_range没问题
    // UnaryFunc, typename boost::range_iterator<Range>::type
    UnaryFunc, typename boost::range_iterator<const Range>::type
> > make_transform_range(
    const Range &range,
    const UnaryFunc &func
) {
    return boost::make_iterator_range(
        boost::make_transform_iterator(
            boost::begin(range), func
        ),
        boost::make_transform_iterator(
            boost::end(range), func
        )
    );
}

template<class RangeTuple>
boost::iterator_range<boost::zip_iterator<
    typename detail::iterator_tuple<RangeTuple>::type
> > make_zip_range(
    RangeTuple &t
) {
    return boost::make_iterator_range(
        boost::make_zip_iterator(detail::make_begin_iterator_tuple(t)),
        boost::make_zip_iterator(detail::make_end_iterator_tuple(t))
    );
}

template<class RangeTuple>
boost::iterator_range<boost::zip_iterator<
    typename detail::iterator_tuple<RangeTuple>::type
> > make_zip_range(
    const RangeTuple &t
) {
    return boost::make_iterator_range(
        boost::make_zip_iterator(detail::make_begin_iterator_tuple(t)),
        boost::make_zip_iterator(detail::make_end_iterator_tuple(t))
    );
}

template<class Range>
boost::iterator_range<
    boost::indirect_iterator<
        typename boost::range_iterator<Range>::type
    >
> make_indirect_range(Range &range) {
    return boost::make_iterator_range(
        boost::make_indirect_iterator(boost::begin(range)),
        boost::make_indirect_iterator(boost::end(range))
    );
}

template<class Range>
boost::iterator_range<
    boost::indirect_iterator<
        typename boost::range_iterator<const Range>::type
    >
> make_indirect_range(const Range &range) {
    return boost::make_iterator_range(
        boost::make_indirect_iterator(boost::begin(range)),
        boost::make_indirect_iterator(boost::end(range))
    );
}

} // ans

#endif

