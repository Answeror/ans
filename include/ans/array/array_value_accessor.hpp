#ifndef ANS_ARRAY_VALUE_ACCESSOR_HPP
#define ANS_ARRAY_VALUE_ACCESSOR_HPP

#include <cstddef>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include "ans/array_fwd.hpp"
#include "ans/array/array_signature_traits.hpp"

namespace ans { namespace detail { namespace array {

template<class Signature>
class array_base {
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename data_type<Signature>::type data_type;
    typedef typename element<Signature>::type element;
    typedef element * iterator;
    typedef const element * const_iterator;
public:
    static const std::size_t dimension = dimension<Signature>::value;
    static const std::size_t volume = volume<Signature>::value;
    static const std::size_t sub_volume = ::ans::detail::array::volume<
        typename sub_signature<Signature>::type
    >::value;
};

template<class Signature>
class value_accessor_one : public array_base<Signature> {
    typedef array_base<Signature> base_type;
public:
    typedef typename base_type::element value_type;
    typedef typename value_type & reference;
    typedef typename const value_type & const_reference;
};

template<class Signature>
class value_accessor_n : public array_base<Signature> {
    typedef array_base<Signature> base_type;
public:
    typedef sub_array<typename sub_signature<Signature>::type> value_type;
    typedef typename value_type reference;
    typedef typename const value_type const_reference;
};

template<class Signature>
class choose_value_accessor_one :
    public boost::mpl::identity<value_accessor_one<Signature> > {};

template<class Signature>
class choose_value_accessor_n :
    public boost::mpl::identity<value_accessor_n<Signature> > {};

template<class Signature>
class value_accessor_generator :
    public boost::mpl::eval_if_c<
        1 == dimension<Signature>::value,
        choose_value_accessor_one<Signature>,
        choose_value_accessor_n<Signature>
    >{};

} // array
} // detail
} // ans

#endif
