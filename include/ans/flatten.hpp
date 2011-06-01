#ifndef ANS_FLATTEN_HPP
#define ANS_FLATTEN_HPP

/*
@author: Answeror
@description:

Flatten a nested tuple.

e.g.

using namespace boost::fusion;

typedef vector<int, const int, int&, const int&> t1;
typedef vector<t1> t2;
typedef vector<const t1> t3;
typedef vector<t1&> t4;
typedef vector<const t1&> t5;

int a0;
t1 a1(a0, a0, a0, a0);
t2 a2(a1);
t3 a3(a1);
t4 a4(a1);
t5 a5(a1);

// Wrong ones have been commented below.
{
    typedef vector<int, int, int, int> t6;
    t6 b1 = ans::flatten(a1);
    t6 b2 = ans::flatten(a2);
    t6 b3 = ans::flatten(a3);
    t6 b4 = ans::flatten(a4);
    t6 b5 = ans::flatten(a5);
}
{
    typedef vector<const int&, const int&, const int&, const int&> t6;
    t6 b1 = ans::flatten(a1);
    t6 b2 = ans::flatten(a2);
    t6 b3 = ans::flatten(a3);
    t6 b4 = ans::flatten(a4);
    t6 b5 = ans::flatten(a5);
}
{
    typedef vector<int&, int&, int&, int&> t6;
    //t6 b1 = ans::flatten(a1);
    //t6 b2 = ans::flatten(a2);
    //t6 b3 = ans::flatten(a3);
    //t6 b4 = ans::flatten(a4);
    //t6 b5 = ans::flatten(a5);
}
{
    typedef vector<int&, int, int&, int> t6;
    //t6 b1 = ans::flatten(a1);
    //t6 b2 = ans::flatten(a2);
    //t6 b3 = ans::flatten(a3);
    t6 b4 = ans::flatten(a4);
    //t6 b5 = ans::flatten(a5);
}
// Use ans::toref to archieve top level ref.
{
    typedef vector<int&, int, int&, int> t6;
    t6 b1 = ans::flatten(ans::toref(a1));
    t6 b2 = ans::flatten(ans::toref(a2));
    //t6 b3 = ans::flatten(ans::toref(a3));
    t6 b4 = ans::flatten(ans::toref(a4));
    //t6 b5 = ans::flatten(ans::toref(a5));
}
*/

#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/value_of.hpp>
#include <boost/fusion/include/deduce.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/ref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/result_of.hpp>

#include "toref.hpp"

namespace ans {

namespace functor {

struct flatten;
struct flatten_step;

} // functor

namespace result_of {

template<class Seq>
struct flatten : 
    boost::mpl::eval_if<
        boost::fusion::traits::is_sequence<Seq>,
        boost::fusion::result_of::fold<
            Seq,
            boost::fusion::vector0<>,
            typename ans::functor::flatten_step
        >,
        // when seq is just a plane element
        boost::mpl::identity<
            boost::fusion::single_view<
                typename boost::fusion::traits::deduce<Seq>::type
            >
        >
    >
{};

} // result_of

template<class Seq>
typename boost::result_of<functor::flatten(const Seq&)>::type
flatten(const Seq &s) {
    return functor::flatten()(s);
}

namespace functor {

struct flatten {
    template<class T>
    struct result;
    
    template<class Seq>
    struct result<flatten(const Seq&)> : ans::result_of::flatten<const Seq> {};

    template<class Seq>
    typename boost::lazy_enable_if< // use lazy enable to avoid eval of result
        boost::fusion::traits::is_sequence<Seq>,
        result<flatten(const Seq&)>
    >::type operator ()(const Seq &s) const {
        return boost::fusion::fold(s, boost::fusion::vector0<>(), flatten_step());
    }
    
    template<class Seq>
    typename boost::lazy_disable_if< // use lazy enable to avoid eval of result
        boost::fusion::traits::is_sequence<Seq>,
        result<flatten(const Seq&)>
    >::type operator ()(const Seq &s) const {
        return typename result<flatten(const Seq&)>::type(s);
    }
}; // flatten

struct flatten_step {
    template<class T>
    struct result;
    
    template<class S, class E>
    struct result<flatten_step(const S&, E&)> :
        boost::fusion::result_of::join<
            const S, // note here, add const
            const typename ans::result_of::flatten<
                const typename ans::result_of::toref<E>::type
            >::type
        >
    {};
    
    template<class S, class E>
    struct result<flatten_step(const S&, const E&)> :
        boost::fusion::result_of::join<
            const S, // note here, add const
            const typename ans::result_of::flatten<const E>::type
        >
    {};
    
    template<class S, class E>
    typename result<flatten_step(const S&, E&)>::type
    operator()(const S &s, E &e) const
    {
        return boost::fusion::join(s, ans::flatten(ans::toref(e)));
    }
    
    template<class S, class E>
    typename result<flatten_step(const S&, const E&)>::type
    operator()(const S &s, const E &e) const
    {
        return boost::fusion::join(s, ans::flatten(e));
    }
}; // flatten_step

} // functor

} // ans

#endif

// old version
//#ifndef ANS_FLATTEN_HPP
//#define ANS_FLATTEN_HPP
//
///*
//@author: Answeror
//@description:
//
//Flatten a nested tuple.
//
//e.g.
//
//using namespace boost::fusion;
//
//vector<int, vector<int, int> > a;
//vector<int, int, int&> b = flatten(a);
//
//const vector<int, vector<int, int> > a;    
//vector<int, int, const int&> b = flatten(a);
//
//vector<int&, int&, int&> b = flatten(make_vector(1, make_vector(1, 1)));
//*/
//
//#include <boost/fusion/include/fold.hpp>
//#include <boost/fusion/include/join.hpp>
//#include <boost/fusion/include/push_back.hpp>
//#include <boost/fusion/include/vector.hpp>
//#include <boost/fusion/include/is_sequence.hpp>
//#include <boost/fusion/include/value_of.hpp>
//#include <boost/utility/enable_if.hpp>
//#include <boost/ref.hpp>
//
//namespace ans {
//
//namespace detail {
//
//struct flatten; // forward declare
//
//} // detail
//
//namespace result_of {
//
//template<class Seq>
//struct flatten : 
//    boost::fusion::result_of::fold<
//        Seq,
//        boost::fusion::vector0<>,
//        ans::detail::flatten
//    >
//{};
//
//} // result_of
//
////template<class Seq>
////typename result_of::flatten<Seq>::type flatten(Seq &s) {
////    return boost::fusion::fold(s, boost::fusion::vector0<>(), detail::flatten());
////}
//
//// use functor instead
//struct flatten_t {
//    template<class T>
//    struct result;
//    
//    template<class Seq>
//    struct result<flatten_t(Seq&)> : result_of::flatten<Seq> {};
//    
//    // run on both const and non-const seq
//    template<class Seq>
//    typename result<flatten_t(Seq&)>::type operator ()(Seq &s) const {
//        return boost::fusion::fold(s, boost::fusion::vector0<>(), detail::flatten());
//    }
//}; // flatten_t
//
//template<class Seq>
//typename flatten_t::template result<flatten_t(Seq&)>::type
//flatten(Seq &s) {
//    return flatten_t()(s);
//}
//
//namespace detail {
//
//struct flatten {
//    template<class T, class Enable = void>
//    struct result;
//    
//    template<class S, class E>
//    struct result<
//        flatten(const S&, E&), 
//        typename boost::enable_if<boost::fusion::traits::is_sequence<E> >::type
//    > :
//        boost::fusion::result_of::join<
//            const S, // note here, add const
//            const typename ans::result_of::flatten<E>::type // note here, add const, but no ref
//        >
//    {};
//    
//    template<class S, class E>
//    struct result<
//        flatten(const S&, E&),
//        typename boost::disable_if<boost::fusion::traits::is_sequence<E> >::type
//    > :
//        boost::fusion::result_of::push_back<
//            const S, // note here, add const
//            boost::reference_wrapper<E> // wrap with ref
//        >
//    {};
//    
//    template<class S, class E>
//    typename boost::lazy_enable_if< // use lazy enable to avoid eval of result
//        boost::fusion::traits::is_sequence<E>,
//        result<flatten(const S&, E&)>
//    >::type operator()(const S &s, E &e) const
//    {
//        return boost::fusion::join(s, ans::flatten(e)); // use join, not push_back
//    }
//
//    template<class S, class E>
//    typename boost::lazy_disable_if<
//        boost::fusion::traits::is_sequence<E>,
//        result<flatten(const S&, E&)>
//    >::type operator()(const S &s, E &e) const
//    {
//        return boost::fusion::push_back(s, boost::ref(e)); // push_back a ref
//    }
//};
//
//} // detail
//
//} // ans
//
//#endif
