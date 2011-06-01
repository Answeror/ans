#ifndef ANS_TOREF_HPP
#define ANS_TOREF_HPP

/*
@author: Answeror
@description:

Make inner reference tuple.

e.g.

using namespace boost::fusion;

vector<int, int> a;
vector<int, int&> b = toref(a);

vector<int, int> a;
vector<int, const int&> b = toref(a);

vector<int&, int&> a = toref(make_tuple(1, 1));
*/

#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/ref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace ans {

namespace functor {

struct toref;
struct toref_step;

}; // functor

namespace result_of {

template<class Seq>
struct toref : 
    boost::mpl::eval_if<
        boost::fusion::traits::is_sequence<Seq>,
        boost::fusion::result_of::fold<
            Seq,
            boost::fusion::vector0<>, // return type of make_vector()
            ans::functor::toref_step
        >,
        boost::mpl::identity<
            boost::reference_wrapper<Seq>
        >
    >
{};

} // result_of

template<class Seq>
typename boost::result_of<functor::toref(Seq&)>::type
toref(Seq &s) {
    return functor::toref()(s);
}

// Use const ref seq to deal with non-const rvalue.
template<class Seq>
typename boost::result_of<functor::toref(const Seq&)>::type
toref(const Seq &s) {
    return functor::toref()(s);
}

namespace functor {

struct toref {
    template<class T>
    struct result;
    
    template<class Seq>
    struct result<toref(Seq&)> : ans::result_of::toref<Seq> {};
    
    template<class Seq>
    struct result<toref(const Seq&)> : ans::result_of::toref<const Seq> {};
    
    template<class Seq>
    typename boost::lazy_enable_if<
        boost::fusion::traits::is_sequence<Seq>,
        result<toref(Seq&)>
    >::type operator ()(Seq &s) const {
        return boost::fusion::fold(s, boost::fusion::vector0<>(), toref_step());
    }
    
    template<class Seq>
    typename boost::lazy_disable_if<
        boost::fusion::traits::is_sequence<Seq>,
        result<toref(Seq&)>
    >::type operator ()(Seq &s) const {
        return boost::ref(s);
    }
    
    template<class Seq>
    typename boost::lazy_enable_if<
        boost::fusion::traits::is_sequence<Seq>,
        result<toref(const Seq&)>
    >::type operator ()(const Seq &s) const {
        return boost::fusion::fold(s, boost::fusion::vector0<>(), toref_step());
    }
    
    template<class Seq>
    typename boost::lazy_disable_if<
        boost::fusion::traits::is_sequence<Seq>,
        result<toref(const Seq&)>
    >::type operator ()(const Seq &s) const {
        return boost::cref(s);
    }
};

struct toref_step {
    template<class T>
    struct result;
    
    template<class S, class E>
    struct result<toref_step(const S&, E&)> :
        boost::fusion::result_of::push_back<
            const S, // note here, add const
            boost::reference_wrapper<E>
        >
    {};
    
    template<class S, class E>
    struct result<toref_step(const S&, const E&)> :
        boost::fusion::result_of::push_back<
            const S, // note here, add const
            boost::reference_wrapper<const E>
        >
    {};

    template<class S, class E>
    typename result<toref_step(const S&, E&)>::type
    operator()(const S &s, E &e) const { // the second argument is non-const
        return boost::fusion::push_back(s, boost::ref(e)); // use ref wrap it
    }
    
    template<class S, class E>
    typename result<toref(const S&, const E&)>::type
    operator()(const S &s, const E &e) const { // the second argument is const
        return boost::fusion::push_back(s, boost::cref(e)); // use cref wrap it
    }
}; // toref

}; // functor
    
} // ans

#endif
