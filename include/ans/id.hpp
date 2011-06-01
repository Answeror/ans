#ifndef ANS_ID_HPP
#define ANS_ID_HPP

/*
<author>Answeror</author>
<create-time>2010-07-27</create-time>
*/

#include <boost/integer_traits.hpp>
#include <boost/operators.hpp>

namespace ans {

template<
    class Value, 
    Value Invalid = boost::integer_traits<Value>::const_max, 
    Value Default = Invalid
>
class id;

template<
    class Value, 
    Value Invalid, 
    Value Default
>
class id : 
    boost::totally_ordered<id<Value, Invalid, Default> >
{
public:
    typedef Value value_type;
    typedef id<Value, Invalid, Default> this_type;
public:
    static id make_invalid() { return id(Invalid); }
    static id make_default() { return id(Default); }
public:
    id() : m_value(make_default().value()) {}
    explicit id(value_type value) : m_value(value) {}
public:
    value_type value() const { return m_value; }
    
    bool valid() const { return *this != make_invalid(); }
    
public:
    friend bool operator ==(id lhs, id rhs) {
        return lhs.value() == rhs.value();
    }
    friend bool operator <(id lhs, id rhs) {
        return lhs.value() < rhs.value();
    }
    
    friend std::istream & operator >>(std::istream &is, id &arg) {
        return is >> arg.m_value;
    }
    
    friend std::ostream & operator <<(std::ostream &os, id arg) {
        return os << arg.m_value;
    }
private:
    value_type m_value;
};

} // ans

#endif
