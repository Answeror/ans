#include "unittest_pimpl.h"

// This internal implementation usually only have destructor, constructors,
// data and probably internal methods. Given it is already internal by design,
// it does not need to be a 'class'. All public methods are declared in the
// external visible Test1 class. Then, data in this structure are accessed as
// (*this)->data or (**this).data.
template<> struct pimpl<Test1>::implementation
{
    implementation () : int_(0)             { printf("Test1::implementation()\n"); }
    implementation (int k) : int_(k)        { printf("Test1::implementation(int)\n"); }
    implementation (int k, int l) : int_(k) { printf("Test1::implementation(int, int)\n"); }
    implementation (Foo&)                   { printf("Test1::implementation(Foo&)\n"); }
    implementation (Foo const&)             { printf("Test1::implementation(Foo const&)\n"); }
    implementation (Foo const&, Foo const&) { printf("Test1::implementation(Foo const&, Foo const&)\n"); }
    implementation (Foo*)                   { printf("Test1::implementation(Foo*)\n"); }
    implementation (Foo const*)             { printf("Test1::implementation(Foo const*)\n"); }
   ~implementation ()                       { printf("Test1::~implementation()\n"); }

    int int_;
};

template<> struct pimpl<Test2>::implementation
{
    implementation () : int_(0)             { printf("Test2::implementation()\n"); }
    implementation (int k) : int_(k)        { printf("Test2::implementation(int)\n"); }
    implementation (int k, int l) : int_(k) { printf("Test2::implementation(int, int)\n"); }
    implementation (Foo&)                   { printf("Test2::implementation(Foo&)\n"); }
    implementation (Foo const&)             { printf("Test2::implementation(Foo const&)\n"); }
   ~implementation ()                       { printf("Test2::~implementation()\n"); }

    int int_;
};

int
Test1::get() const
{
    // The standard access to the implementation.
    implementation const& self = **this;

    int k1 = (*this)->int_;
    int k2 = (**this).int_;

    return k1;
}

Test1::Test1 () : base() {}                     // Call implementation::implementation()
Test2::Test2 () : base() {}                     // ditto
Test1::Test1 (int k) : base(k) {}               // Call implementation::implementation(int)
Test2::Test2 (int k) : base(k) {}               // ditto
Test1::Test1 (int k, int l) : base(k, l) {}     // Call implementation::implementation(int, int)

Test1::Test1 (Foo&       foo) : base(foo) {}    // Make sure 'const' handled properly
Test1::Test1 (Foo const& foo) : base(foo) {}    // Make sure 'const' handled properly
Test1::Test1 (Foo*       foo) : base(foo) {}    // Make sure 'const' handled properly
Test1::Test1 (Foo const* foo) : base(foo) {}    // Make sure 'const' handled properly
Test1::Test1 (Foo const& f1, Foo const& f2) : base(Foo(), f2) {} // Make sure 'const' handled properly
// The case above fails unless we have all those constructors handling references and constant references.

Test1::Test1 (null_like_type) : base(null<Test1>()) {}   // Create an invalid Pimpl (like NULL)
Test2::Test2 (null_like_type) : base(null<Test2>()) {}   // ditto

static Test1 single;
static Test1 const const_single;
Test1::Test1 (singleton_type) : base(single) {} // 'single' is used as a Singleton.

int
Test2::get() const
{
    implementation const& self = **this;

    int k1 = (*this)->int_;
    int k2 = (**this).int_;

    return k1;
}

void
Test2::set(int v)
{
    (*this)->int_ = v;
}

bool
Test2::operator==(Test2 const& that) const
{
    return (**this).int_ == (*that).int_;
}

///////////////////////////////////////////////////
// Testing polymorphism
///////////////////////////////////////////////////

typedef pimpl<Base>::implementation BaseImpl;

template<> struct pimpl<Base>::implementation
{
    implementation (int k) : base_int_(k) { printf("Base::implementation(int)\n"); }
    virtual ~implementation ()            { printf("Base::~implementation()\n"); }
    virtual void call_virtual() { printf("Base::call_virtual\n"); }

    int base_int_;
};

struct Derived1Impl : public BaseImpl
{
    typedef BaseImpl base;

    Derived1Impl (int k, int l) : base(k), derived_int_(l)
    {
        printf("Derived1::implementation(int,int)\n");
    }
   ~Derived1Impl ()
    {
        printf("Derived1::~implementation()\n");
    }
    virtual void call_virtual() { printf("Derived1::call_virtual\n"); }

    int derived_int_;
};

struct Derived2Impl : public Derived1Impl
{
    typedef Derived1Impl base;

    Derived2Impl (int k, int l, int m) : base(k, l), more_int_(m)
    {
        printf("Derived2::implementation(int,int)\n");
    }
   ~Derived2Impl ()
    {
        printf("Derived2::~implementation()\n");
    }
    virtual void call_virtual() { printf("Derived2::call_virtual\n"); }

    int more_int_;
};

//Base::Base(int k) : base(k)
//{
//}
// The commented Base::Base(int) above does the same as the one below.
// Doing it via reset() simply for consistency sake with derived classes.
// What it does it initially sets the underlying pimpl to 0 and then resets
// it to the appropriate implementation.
Base::Base(int k) : base(null())
{
    reset(new BaseImpl(k));
}
Derived1::Derived1(int k, int l) : Base(null<Base>())
{
    reset(new Derived1Impl(k, l));
}
Derived2::Derived2(int k, int l, int m) : Derived1(null<Derived1>())
{
    reset(new Derived2Impl(k, l, m));
}

void
Base::call_virtual()
{
    (*this)->call_virtual();
}
