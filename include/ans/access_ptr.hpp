#ifndef ANS_ACCESS_PTR_HPP
#define ANS_ACCESS_PTR_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

This class is used to abstract out the common things of shared_ptr<T> and
function<T&()>.
We use shared_ptr<T> to make object shared and use function<T&()> to express a
accessor that always return a valid T& but not necessary the same one.
So access_ptr<T> could accept either a shared_ptr<T> or a function<T&()> that
have the syntax of shared_ptr<T> and the semantics function<T&()>.
--------------------------------------------------------------------------------
*/

#include <cassert>

#include <boost/shared_ptr.hpp>
#include <boost/function/function0.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include "access_ptr_fwd.hpp"
#include "shared_accessor.hpp"

namespace ans {

template<class T>
class access_ptr {
public:
    typedef access_ptr<T> this_type;
    typedef T *pointee;
    typedef T &reference;
    typedef T element_type;
    typedef boost::function<T&()> accessor;
    
public:
    // Use this constructor carefully.
    access_ptr() : f() {}

    /// construct from a functor directly
    explicit access_ptr(const accessor &f) : f(f) {}

    /// construct from a rvalue functor directly
    explicit access_ptr(accessor &&f) : f(std::move(f)) {}
    
    // Convert from shared_ptr with other value type.
    template<class U>
    explicit access_ptr(boost::shared_ptr<U> p) : 
        f(make_shared_accessor(p))
    {
        //assert(p && "Null pointer.");
    }
    
    //// Convert from other accessor.
    //template<class Accessor>
    //access_ptr(
    //    Accessor get, 
    //    typename boost::enable_if<
    //        typename boost::is_convertible<Accessor, accessor>
    //    >::type *dumb = 0
    //) :
    //    f(get)
    //{
    //    //assert(f && "Invalid accessor.");
    //}

    access_ptr(const accessor &get) : f(get) {}

    //access_ptr(const this_type &other) : f(other.f) {}
    
    pointee get() const {
        assert(f);
        return &f();
    }
    
    pointee operator ->() const {
        assert(f);
        return get();
    }
    
    reference operator *() const {
        assert(f);
        return *get();
    }
    
    // Implementing an implicit conversion to bool (operator bool() const) is very convenient and
    // tempting to be deployed in constructs like "if (pimpl)" and "if (!pimpl)" (without explicit
    // operator!()). However, DO NOT IMPLEMENT "operator bool()" as that conversion kicks in way
    // too often and unexpectedly. Like "pimpl + 1", "1 + pimpl" or potentially during
    // boost::lexical_cast<std::string>(pimpl) (if there are no >> and << defined for streams).
    // Consequently, that implicit-conversion-to-bool functionality is to be implemented in an
    // indirect way via an implicit conversion to some pointer type. The best type for the purpose
    // appears to be a pointer to a member function. For more see the chapter 7.7 in Alexandrescu's
    // "Modern C++ Design" and how that functionality is implemented for boost::shared_ptr.
    
    void internal_bool() {};
    typedef void (this_type::*bool_type)();
    operator bool_type() const { return f ? &this_type::internal_bool : 0; }

private:
    accessor f;
};

// Used to support boost::bind.
template<class T>
inline T * get_pointer(const access_ptr<T> &p) {
    return p.get();
}

} // ans

#endif
