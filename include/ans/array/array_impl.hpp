#ifndef ANS_ARRAY_IMPL_HPP
#define ANS_ARRAY_IMPL_HPP

#include "ans/array_fwd.hpp"
#include "ans/array/array_signature_traits.hpp"
#include "ans/array/array_value_accessor.hpp"

namespace ans { namespace detail { namespace array {

template<class Signature>
class array_impl :
    public value_accessor_generator<Signature>::type {
    typedef typename value_accessor_generator<Signature>::type types;
public:
    typedef typename types::data_type data_type;
    typedef typename types::element element;
    typedef typename types::value_type value_type;
    typedef typename types::size_type size_type;
    typedef typename types::reference reference;
    typedef typename types::const_reference const_reference;
//public:
//    static reference access(element *data, size_type i) {
//        return *(data + i * sub_volume);
//    }
//    static const_reference access(const element *data, size_type i) {
//        return *(data + i * sub_volume);
//    }
};

} // array
} // detail
} // ans

#endif
