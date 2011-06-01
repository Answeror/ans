#ifndef ANS_DEFAULT_HPP
#define ANS_DEFAULT_HPP

/*
<author>Answeror</author>
<create-time>2010-07-27</create-time>
*/

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace ans {

struct use_default_t {};

static use_default_t use_default;

template<class T> class has_default {
public:
    has_default(const T &data) : 
        m_data(boost::make_shared<T>(data)), 
        m_default(false) {}
    has_default(use_default_t) : m_data(), m_default(true) {}
    has_default(const has_default &other) :
        m_data(other.m_data), 
        m_default(other.m_default) {}
    operator T() const { return get(); }
    T get() const { return *m_data; }
    bool is_default() const { return m_default; }
private:
    boost::shared_ptr<T> m_data;
    bool m_default;
};

template<class T> class has_default<T &> {
public:
    has_default(T &data) : m_data(&data), m_default(false) {}
    has_default(use_default_t) : m_data(0), m_default(true) {}
    has_default(const has_default &other) :
        m_data(other.m_data), m_default(other.m_default) {}
    operator T() const { return get(); }
    T get() const { return *m_data; }
    bool is_default() const { return m_default; }
private:
    T *m_data;
    bool m_default;
};

} // ans

#endif
