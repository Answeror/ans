#ifndef ANS_SERIALIZABLE_HPP
#define ANS_SERIALIZABLE_HPP

/*
<author>Answeror</author>
<create-time>2010-08-20</create-time>
<description>
Describe a serializable interface.
</description>
*/

#include <iosfwd>

#include "crtp.hpp"

namespace ans {

template<class Derived>
struct serializable : crtp<Derived> {
    typedef serializable this_type;

    friend std::ostream & serialize(std::ostream &os, const this_type &arg) {
        return os << arg.derived();
    }
    
    friend std::ostream & operator <<(std::ostream &os, const this_type &arg) {
        return serialize(os, arg.derived());
    }
    
    friend std::istream & deserialize(std::istream &is, this_type &arg) {
        return is >> arg.derived();
    }
    
    friend std::istream & operator >>(std::istream &is, this_type &arg) {
        return deserialize(is, arg.derived());
    }
};

} // ans

#endif
