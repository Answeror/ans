#ifndef ANS_ARRAY_HPP
#define ANS_ARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <boost/type_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include "ans/array_fwd.hpp"
#include "ans/array/array_signature_traits.hpp"
#include "ans/array/array_value_accessor.hpp"
#include "ans/array/array_impl.hpp"
#include "ans/sub_array.hpp"
#include "ans/array/plane.hpp"
#include "ans/array/transform.hpp"

namespace ans {

template<class Signature>
class array {
public:
    typedef array<Signature> this_type;
    
    typedef detail::array::array_impl<Signature> impl;
    typedef typename impl::data_type data_type;
    typedef typename impl::element element;
    typedef typename impl::value_type value_type;
    typedef typename impl::size_type size_type;
    typedef typename impl::reference reference;
    typedef typename impl::const_reference const_reference;
public:
    static const std::size_t volume = impl::volume;
    static const std::size_t sub_volume = impl::sub_volume;
public:
    reference operator [](std::size_t i) {
        return data[i];
    }
    template<size_type N>
    typename transform<this_type, plane<N> >::result_type operator [](plane<N> p) {
        typedef typename transform<Signature, plane<N> >::type array_type;
        return array_type(data, ;
    }
    array & operator =(element elem) {
        std::fill_n(reinterpret_cast<element *>(data), volume, elem);
        return *this;
    }
public:
    data_type data;
};

} // ans

#endif
