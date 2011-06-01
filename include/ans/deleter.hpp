#ifndef ANS_DELETER_HPP
#define ANS_DELETER_HPP

/*
<author>Answeror</author>
<create-time>2010-07-28</create-time>
<description>
The deleter class is used to support shared_ptr
or used as functor to delete all the things in range.
</description>
*/

namespace ans {

namespace tag {
    struct null;
    struct common;
}

template<class Tag = tag::common>
class deleter {
    template<class T> void operator ()(T *p) const { delete p; }
};

template<>
struct deleter<tag::null> {
    template<class T> void operator ()(T *p) const { }
};

} // ans

#endif
