#ifndef ANS_AT_C_HPP
#define ANS_AT_C_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

Used to support GetTransition, GetRotation, etc in Me::Frame and Me::Track.
--------------------------------------------------------------------------------
*/

#include <boost/fusion/include/at_c.hpp>

namespace ans { namespace fn {

// Extract element from a fusion::vector at specific position.
template<size_t N>
struct at_c {
    template<class T>
    struct result;
    
    template<class T>
    // Note, use value_at_c rather than at_c.
    struct result<const at_c(T)> : boost::fusion::result_of::value_at_c<T, N> {};
    
    // Following code will crush the compiler in VS2008...
    //template<class T>
    //struct result<const Extract(const T&)> : result<const Extract(T)> {};
    
    template<class T>
    typename result<const at_c(T)>::type
    operator ()(const T &t) const {
        return boost::fusion::at_c<N>(t);
    };
}; // at_c

} // fn
} // ans

#endif
