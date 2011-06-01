#ifndef ANS_CRTP_HPP
#define ANS_CRTP_HPP

/*
<author>Answeror</author>
<create-time>2010-08-20</create-time>
<description>
Used to support CRTP doing downcast.
</description>
*/

namespace ans {

template<class Derived>
class crtp {
public:
    typedef Derived derived_type;
    
protected:
    const derived_type & derived() const {
        return *static_cast<const derived_type*>(this);
    }
    
    derived_type & derived() {
        return *static_cast<derived_type*>(this);
    }
};

} // ans

#endif
