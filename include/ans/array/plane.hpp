#ifndef ANS_PLANE_HPP
#define ANS_PLANE_HPP

#include <cstddef>
#include <boost/mpl/integral_c.hpp>

#include "ans/array_fwd.hpp"

namespace ans {

template<std::size_t N>
struct plane : boost::mpl::integral_c<std::size_t, N> {};

} // ans

#endif
