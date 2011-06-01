#ifndef ANS_GUARD_HPP
#define ANS_GUARD_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: Scope guard.
@usage: guard g = make_guard([](){ delete p; });
--------------------------------------------------------------------------------
*/

namespace ans {

class guard_base
{
public:
    guard_base() : rollback(true) {}
    ~guard_base() {}

protected:
    guard_base(const guard_base &other) : rollback(rollback)
    {
        other.commit();
    }

private:
    void operator =(const guard_base&); // disable assignment

public:
    void commit() const { rollback = false; }

protected:
    mutable bool rollback;
}; // guard_base

typedef const guard_base &guard;

template<class Fn>
class guard_impl : public guard_base
{
public:
    guard_impl(Fn fn) : fn(fn) {}
    ~guard_impl() { if (rollback) fn(); }

private:
    Fn fn;
}; // guard_impl

template<class Fn>
inline guard_impl<Fn> make_guard(Fn fn)
{
    return guard_impl<Fn>(fn);
}

} // ans

#endif // ANS_GUARD_HPP
