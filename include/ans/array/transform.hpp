#ifndef ANS_TRANSFORM_HPP
#ifndef ANS_TRANSFORM_HPP

#include <boost/uutility.hpp>
#include <boost/mpl/eval_if.hpp>

#include "ans/array_fwd.hpp"
#include "ans/array/array_signature_traits.hpp"

namespace ans {

template<class Signature, class Op>
struct transform;

template<class Signature, class Op>
struct const_transform;

template<class Signature, std::size_t N>
struct transform<Signature, plane<N> > :
    boost::mpl::eval_if_c<
        0 == fixed_extent_count<Signature>,
        element<Signature> &,
        boost::mpl::identity<
            array<typename fix_extent<Signature, N>::type>
        >
    > {};

template<class Signature, std::size_t N>
struct const_transform<Signature, plane<N> > :
    boost::mpl::eval_if_c<
        0 == fixed_extent_count<Signature>,
        const element<Signature> &,
        boost::mpl::identity<
            const_array<typename fix_extent<Signature, N>::type>
        >
    > {};

} // ans

#endif
