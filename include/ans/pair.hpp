#ifndef ANS_PAIR_HPP
#define ANS_PAIR_HPP

/*
<author>Answeror</author>
<last-modify-time>2010-08-23</last-modify-time>
*/

#include <utility>
#include <boost/compressed_pair.hpp>
#include <boost/swap.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/implicit_cast.hpp>

namespace ans {

template<class T1, class T2 = T1>
class pair : public boost::compressed_pair<T1, T2> {
public:
    typedef boost::compressed_pair<T1, T2> base_type;
    typedef typename base_type::first_param_type first_param_type;
    typedef typename base_type::second_param_type second_param_type;
    
    using base_type::first;
    using base_type::second;
    
public:
    pair() : base_type() {}
    //template<class U>
    //pair(U arg1, U arg2) : base_type(arg1, arg2) {}
    pair(first_param_type arg1, second_param_type arg2) : base_type(arg1, arg2) {}
    template<class U1, class U2>
    pair(U1 arg1, U2 arg2) : base_type(arg1, arg2) {}
    template<class U1, class U2>
    pair(const pair<U1, U2> &other) : base_type(other.first(), other.second()) {}
    template<class U1, class U2>
    pair(const std::pair<U1, U2> &other) : base_type(other.first, other.second) {}
    template<class U1, class U2>
    pair(const boost::compressed_pair<U1, U2> &other) : 
        base_type(other.first(), other.second()) {}
    
    //@2010-12-11 added
    template<class Sequence>
    pair(
        const Sequence &s, 
        typename boost::enable_if<
            boost::fusion::traits::is_sequence<Sequence>
        >::type *dump = 0
    ) : base_type(
        // note cannot dereference directly
        // TODO: why?
        //*boost::fusion::begin(s), 
        //*boost::fusion::next(boost::fusion::begin(s))
        boost::fusion::deref(boost::fusion::begin(s)), 
        boost::fusion::deref(boost::fusion::next(boost::fusion::begin(s)))
    ) {}
public:
    template<class U1, class U2>
    pair & operator =(pair<U1, U2> other) {
        //boost::swap(*this, other);
        boost::swap(
            boost::implicit_cast<base_type&>(*this),
            boost::implicit_cast<base_type&>(other)
        );
        return *this;
    }
    template<class U1, class U2>
    bool operator ==(pair<U1, U2> other) {
        return first() == other.first() && second() == other.second();
    }
    template<class U1, class U2>
    bool operator !=(pair<U1, U2> other) {
        return !(*this == other);
    }
};

template<class T1, class T2> 
inline pair<T1, T2> make_pair(T1 t1, T2 t2) {
    return pair<T1, T2>(t1, t2);
}

template<class T> 
inline pair<T, T> make_pair(T arg) {
    return pair<T, T>(arg, arg);
}

template<class T1, class T2> 
inline pair<T1&, T2&> make_ref_pair(T1 &t1, T2 &t2) {
    return pair<T1&, T2&>(t1, t2);
}

template<class T1, class T2> 
inline pair<const T1&, const T2&> make_cref_pair(const T1 &t1, const T2 &t2) {
    return pair<const T1&, const T2&>(t1, t2);
}

} // ans

#endif
