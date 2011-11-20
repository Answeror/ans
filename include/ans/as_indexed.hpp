#ifndef ANS_AS_INDEXED_HPP
#define ANS_AS_INDEXED_HPP

/*
@author: Answeror
@description:
Transform index to elem at this index.
Note target range is passed by value to support rvalue, so use
boost::iterator_range to wrap when use container rather than range.
*/

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
    #define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#include <boost/utility/declval.hpp>
#include <boost/range/adaptor/transformed.hpp>

// oven的实现里fn是以引用传递的, 只能用在一个完整的表达式中.
#include <pstade/oven/transformed.hpp>

#include <ans/parenthesis_as_bracket.hpp>

namespace ans
{
    namespace as_indexed_detail
    {
        namespace others = boost::adaptors;
    }

    namespace adaptors
    {
        /// 如果要保存引用, 就传入boost.iterator_range或者boost.reference_wrapper.
        template<class T>
        inline decltype(as_indexed_detail::others::transformed(ans::make_parenthesis_as_bracket(boost::declval<T>())))
            as_indexed(T t)
        {
            return as_indexed_detail::others::transformed(ans::make_parenthesis_as_bracket(t));
        }
    }
}

//#include <boost/range/adaptor/transformed.hpp>
//#include <boost/range/reference.hpp>
//#include <boost/type_traits/remove_reference.hpp>
//
//namespace ans {
//
//namespace range_detail {
//
//template<class T>
//struct as_index {
//    typedef typename boost::range_reference<T>::type result_type;
//    T *t;
//    as_index() {}
//    explicit as_index(T &t) : t(&t) {}
//    template<class Index>
//    result_type operator ()(Index i) const { return (*t)[i]; }
//};
//
//template<class R, class T>
//struct as_index_range : boost::transformed_range<as_index<T>, const R> {
//private:
//    typedef as_index<T> fn;
//    typedef boost::transformed_range<fn, const R> base;
//
//public:
//    as_index_range(const R &r, T &t) : base(fn(t), r) {}
//}; // as_index_range
//
//template<class T>
//struct as_index_holder : 
//    boost::range_detail::holder<T&>
//{
//    as_index_holder(T &t) :
//        boost::range_detail::holder<T&>(t)
//    {}
//};
//
////template<class InputRange, class T>
////inline as_index_range<InputRange, T>
////operator |(InputRange &r, const as_index_holder<T&> &t) {
////    return as_index_range<InputRange, T>(r, t.val);
////}
//
//template<class InputRange, class T>
//inline as_index_range<InputRange, T>
//operator |(const InputRange &r, const as_index_holder<T> &t) {
//    return as_index_range<InputRange, T>(r, t.val);
//}
//
//template<class InputRange, class T>
//inline as_index_range<InputRange, const T>
//operator |(const InputRange &r, const as_index_holder<const T> &t) {
//    return as_index_range<InputRange, const T>(r, t.val);
//}
//
//} // range_detail
//
//using range_detail::as_index_range;
//
//namespace adaptors {
//
//namespace {
//    const boost::range_detail::forwarder<
//        range_detail::as_index_holder
//    > as_indexed;
//}
//
//} // adaptors
//
//} // ans
//
#endif
