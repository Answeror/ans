#ifndef ANS_SUB_ARRAY_HPP
#define ANS_SUB_ARRAY_HPP

#include "ans/array_fwd.hpp"
#include "ans/array/array_impl.hpp"

namespace ans {

template<class Signature>
class sub_array {
    typedef detail::array::array_impl<Signature> impl;
public:
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
    sub_array(data_type &data) : data(data) {}
public:
    reference operator [](std::size_t i) {
        return data[i];
    }
    const_reference operator [](std::size_t i) const {
        return data[i];
    }
    sub_array & operator =(element elem) {
        std::fill_n(reinterpret_cast<element *>(data), volume, elem);
        return *this;
    }
public:
    data_type &data;
};

} // ans

#endif
