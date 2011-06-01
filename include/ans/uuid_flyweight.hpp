#ifndef ANS_UUID_FLYWEIGHT_HPP
#define ANS_UUID_FLYWEIGHT_HPP

/*
<author>Answeror</author>
<create-time>2010-08-13</create-time>
<description>
Used to support boost::flyweight witch use uuid_class.
</description>
*/

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>

#include "uuid_class.hpp"

namespace ans {

template<class T, class Enable = void>
class uuid_flyweight;

template<class T>
class uuid_flyweight<
    T, 
    // T must derived from ans::uuid_class
    typename boost::enable_if<
        boost::is_base_of<uuid_class, T>
    >::type
> : public boost::flyweight<boost::flyweights::key_value<
    boost::uuids::uuid, 
    T, 
    ans::uuid_class::uuid_extractor
> > {
public:
    typedef boost::flyweight<boost::flyweights::key_value<
        boost::uuids::uuid, 
        T, 
        ans::uuid_class::uuid_extractor
    > > base_type;
public:
    uuid_flyweight() : base_type() {}
    uuid_flyweight(const T &arg) : base_type(arg) {}
};

} // ans

#endif
