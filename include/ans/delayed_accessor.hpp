#ifndef ANS_DELAYED_ACCESSOR_H
#define ANS_DELAYED_ACCESSOR_H

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: This class act as a construct-only-when-necessory holder.
--------------------------------------------------------------------------------
*/

#include <cassert>

#include <boost/function/function0.hpp>
#include <boost/concept_check.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace ans {

template<class T>
class delayed_accessor {
public:
    typedef boost::function<T()> factory_type;
    typedef T result_type;
    
    BOOST_CONCEPT_ASSERT((boost::DefaultConstructible<T>));
    BOOST_CONCEPT_ASSERT((boost::CopyConstructible<T>));
    BOOST_CONCEPT_ASSERT((boost::Assignable<T>));
    
public:
    template<class Factory>
    explicit delayed_accessor(Factory make) : 
        impl(boost::make_shared<impl_t>(make, true))
    {
        assert(this->impl->make && "Invalid factory.");
    }
    
    result_type operator ()() const {
        if (impl->first) {
            impl->first = false;
            impl->data = impl->make();
        }
        return impl->data;
    }
    
private:
    // Use shared_ptr here to ensure make() will be called only once.
    // And every accessor order to have this pointer semantics, because
    // accessor just act as a handle.
    struct impl_t {
        factory_type make;
        bool first;
        T data;
        impl_t(factory_type make, bool first) : make(make), first(first) {}
    };
    boost::shared_ptr<impl_t> impl;
}; // delayed_accessor

template<class Factory>
inline delayed_accessor<
    typename boost::remove_reference<
        typename boost::result_of<Factory()>::type
    >::type
> make_delayed_accessor(Factory factory) {
    typedef typename boost::remove_reference<
        typename boost::result_of<Factory()>::type
    >::type value_type;
    return delayed_accessor<value_type>(factory);
}

} // ans

#endif
