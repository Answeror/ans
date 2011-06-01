#ifndef ANS_ARRAY_SIGNATURE_TRAITS
#define ANS_ARRAY_SIGNATURE_TRAITS

#include <cstddef>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/eval_if.hpp>

#include "../array_fwd.hpp"

namespace ans { namespace detail { namespace array {

template<class Signature>
struct sub_signature;

template<class T, std::size_t N>
struct sub_signature<T[N]> : boost::remove_extent<T[N]> {};

// this metafunction used to check the signature to ensure no extent in
// signature equal to fixed_extent<Signature>::value
template<class Signature>
struct data_type : boost::mpl::identity<Signature> {};

template<class Signature>
struct sub_data_type : sub_signature<Signature> {};

template<class Signature>
struct value_type : sub_data_type<Signature> {};

template<class Signature>
struct element;

template<class T, std::size_t N>
struct element<T[N]> : boost::remove_all_extents<
    typename data_type<T[N]>::type
> {};

template<class Signature>
struct dimension : boost::rank<
    typename data_type<Signature>::type
> {};

template<class Signature>
struct volume : boost::mpl::integral_c<
    std::size_t, 
    sizeof(typename data_type<Signature>::type) / 
        sizeof(typename element<Signature>::type)
> {};

struct fixed_extent {
    static const std::size_t value = 1;
};

template<class Signature>
struct access_type : boost::mpl::eval_if_c<
    fixed_extent::value == boost::extent<Signature>::value,
    access_type<typename boost::remove_extent<Signature>::type>,
    boost::mpl::identity<Signature>
> {};

template<class Signature>
struct sub_access_type : access_type<
    typename boost::remove_extent<
        typename access_type<Signature>::type
    >::type
> {};

template<class Signature>
struct fixed_extent_count;

template<class T>
struct fixed_extent_count : boost::mpl::integral_c<std::size_t, 0> {};

template<class T, std::size_t N>
struct fixed_extent_count<T[N]> : boost::mpl::integral_c<
    std::size_t, 
    fixed_extent_count<T>::value
> {};

template<class T>
struct fixed_extent_count<T[fixed_extent::value]> : boost::mpl::integral_c<
    std::size_t, 
    1 + fixed_extent_count<T>::value
> {};

template<class Signature>
struct valid_extent_count : boost::mpl::integral_c<
    std::size_t, 
    boost::rank<Signature>::value - fixed_extent_count<Signature>::value
> {};

// this class used to access elem in array in a variable way,
// the index passed in as an array
struct access {
    template<class Signature>
    static typename element<Signature>::type & apply(
        typename data_type<Signature>::type & data,
        const std::size_t *index
    ) {
        return access::apply<
            typename sub_signature<Signature>::type
        >(
            data[*index],
            index + 1
        );
    }
    template<class Signature>
    static const typename element<Signature>::type & apply(
        const typename data_type<Signature>::type & data,
        const std::size_t *index
    ) {
        return access::apply<
            typename sub_signature<Signature>::type
        >(
            data[*index],
            index + 1
        );
    }
    template<class T>
    static T & apply(
        T & data,
        const std::size_t *index
    ) {
        return data;
    }
};

template<class T, std::size_t E, std::size_t N = 0>
struct change_extent;

template<class T, std::size_t R, std::size_t E>
struct change_extent<T[R], E, 0> {
    typedef T type[E];
};

template<class T, std::size_t R, std::size_t E, std::size_t N>
struct change_extent<T[R], E, N> {
    typedef typename change_extent<T, E, N - 1>::type type[N];
};

// nth non fixed dimension number
template<class T, std::size_t N = 0>
struct non_fixed_dimension;

template<class T, std::size_t R>
struct non_fixed_dimension<T[R], 0> : 
    boost::mpl::integral_c<std::size_t, 0> {};

template<class T>
struct non_fixed_dimension<T[fixed_extent::value], 0> : 
    non_fixed_dimension<T, 0> {};

template<class T, std::size_t R, std::size_t N>
struct non_fixed_dimension<T[R], N> : 
    boost::mpl::integral_c<
        std::size_t,
        1 + non_fixed_dimension<T, N - 1>::value
    > {};

template<class T, std::size_t N>
struct non_fixed_dimension<T[fixed_extent::value], N> : 
    boost::mpl::integral_c<
        std::size_t,
        1 + non_fixed_dimension<T, N>::value
    > {};

template<class T, std::size_t N = 0>
struct fix_extent : change_extent<
    T, 
    fixed_extent::value, 
    non_fixed_dimension<T, N>::value
> {};

// remove dimensions whose extent is fixed
template<class T>
struct remove_fixed : boost::mpl::identity<T> {};

template<class T>
struct remove_fixed<T[fixed_extent::value]> : remove_fixed<T> {};

template<class T, std::size_t N>
struct remove_fixed<T[N]> : boost::mpl::identity<
    typename remove_fixed<T>::type[N]
> {};

} // array
} // detail
} // ans

#endif
