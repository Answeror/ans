#ifndef ANS_SINGLETON_HPP
#define ANS_SINGLETON_HPP

#include <boost/functional/value_factory.hpp>

namespace ans {

template<class T, class Factory = boost::value_factory<T> >
class singleton {
public:
    static T & get() {
        static Factory f;
        static T res = f();
        return res;
    }
}; // singleton

} // ans

#endif
