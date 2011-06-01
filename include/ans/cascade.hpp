#ifndef ANS_CASCADE_HPP
#define ANS_CASCADE_HPP

/*
<author>Answeror</author>
<create-time>2010-08-23</create-time>
<description>
Used to make cascade action, like object invalidation in Ogre.
</description>
*/

#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>

#include "crtp.hpp"
#include "static_assert.hpp"

namespace ans {

template<class Derived>
class cascade : public crtp<Derived> {
public:
    typedef cascade<Derived> this_type;
    
public:
    cascade() {}
    
    template<class OtherDerived>
    cascade(cascade<OtherDerived> &dependence) {
        add_dependence(dependence);
    }
    
    template<class InputIterator>
    cascade(const boost::iterator_range<InputIterator> &dependence) {
        typedef typename boost::iterator_reference<InputIterator>::type Other;
        foreach (Other single, dependence) {
            add_dependence(single);
        }
    }

public:
    template<class OtherDerived>
    void add_dependence(cascade<OtherDerived> &dependence) {
        dependence.m_sig.connect(
            boost::bind(&this_type::onfire<OtherDerived>, this, _1)
        );
    }
    
    template<class OtherDerived>
    void remove_dependence(cascade<OtherDerived> &dependence) {
        dependence.m_sig.disconnect(
            boost::bind(&this_type::onfire<OtherDerived>, this, _1)
        );
    }
    
    // convenient function
    template<class OtherDerived>
    this_type & operator +=(cascade<OtherDerived> &dependence) {
        add_dependence(dependence);
        return *this;
    }
    
    // convenient function
    template<class OtherDerived>
    this_type & operator -=(cascade<OtherDerived> &dependence) {
        remove_dependence(dependence);
        return *this;
    }

public:
    void fire() { onfire(this->derived()); }
    
    template<class OtherDerived>
    void onfire(OtherDerived &arg) {
        if (&derived_type::onfire != &this_type::onfire<OtherDerived>) {
            this->derived().onfire(arg);
        }
        m_sig(this->derived());
    }
    
private:
    boost::signal<void(Derived&)> m_sig;
    
private:
    template<class OtherDerived>
    friend class cascade;
};

} // ans

#endif
