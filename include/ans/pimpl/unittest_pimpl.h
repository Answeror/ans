#ifndef UNITTEST_PIMPLE_HEADER_VB
#define UNITTEST_PIMPLE_HEADER_VB

#include "pimpl.h"
//#include <auxiliary/pimpl.h>

struct singleton_type {};
struct null_like_type {};

struct Foo
{
};

struct Test1 : public pimpl<Test1>::pointer_semantics
{
    // Pure interface.
    // The implementation is hidden in unittest_pimpl_implementation.cpp

    Test1 ();
    Test1 (int);
    Test1 (int, int);
    Test1 (Foo&);
    Test1 (Foo const&);
    Test1 (Foo const&, Foo const&);
    Test1 (Foo*);
    Test1 (Foo const*);
    Test1 (null_like_type);
    Test1 (singleton_type);

    int get() const;
};

struct Test2 : public pimpl<Test2>::value_semantics
{
    // Pure interface.
    // The implementation is hidden in unittest_pimpl_implementation.cpp

    Test2 ();
    Test2 (int);
    Test2 (null_like_type);

    // Value-semantics Pimpl must explicitly define op==()
    // if it wants to be comparable. The same as normal classes do.
    bool operator==(Test2 const&) const;

    int get() const;
    void set(int);
};

struct Base : public pimpl<Base>::pointer_semantics
{
    void call_virtual();
    Base (int);
};

struct Derived1 : public Base
{
    Derived1 (int, int);
};

struct Derived2 : public Derived1
{
    Derived2 (int, int, int);
};


#endif // UNITTEST_PIMPLE_HEADER_VB
