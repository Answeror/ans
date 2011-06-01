#include "unittest_pimpl.h"
#include <string>

int
main()
{
    singleton_type singleton;
    null_like_type null_like;
    Foo foo;
    Foo const const_foo = foo;
    Foo& ref = foo;
    Foo const& const_ref = const_foo;

    Test1 pt11;                     // calls implementation().
    Test2 vt11;                     // calls implementation().
    Test1 pt12(5);                  // calls implementation(int).
    Test2 vt12(5);                  // calls implementation(int).
    Test1 pt13 = pt12;              // calls base(base const&).
    Test2 vt13 = vt12;              // calls base(base const&).
    Test1 pt14(pt12);               // calls base(base const&).
    Test2 vt14(vt12);               // calls base(base const&).
    Test1 pt15(5, 6);               // calls implementation(int, int).
    Test1 pt16(singleton);          // All instances share one instance (singleton).
    Test1 pt17(null_like);          // Create an invalid instance (like NULL).
    Test2 vt17(null_like);          // Create an invalid instance (like NULL).
    Test1 pt18(foo);                // calls implementation(Foo&).
    Test1 pt19(const_foo);          // calls implementation(Foo const&).
    Test1 pt20(ref);                // calls implementation(Foo&).
    Test1 pt21(const_ref);          // calls implementation(Foo const&).
    Test1 pt22(&foo);               // calls implementation(Foo&).
    Test1 pt23(&const_foo);         // calls implementation(Foo const&).
//  Test1 pt24(Foo());              // VS2005 get confused.

    pt11 = pt19;

    bool pcheck1 = pt12 == pt13;    // calls pimpl::op==()
    bool vcheck1 = vt12 == vt13;    // calls Test2::op==()
    bool pcheck2 = pt12 != pt13;    // calls pimpl::op!=()
    bool vcheck2 = vt12 != vt13;    // calls pimpl::op!=() and then Test2::op==()
//  bool pcheck3 = pt12 == 0;       // Requires operator int().
//  bool vcheck3 = vt12 == 0;       // Requires operator int().
//  bool pcheck4 = 0 == pt12;       // Requires operator int().
//  bool vcheck4 = 0 == vt12;       // Requires operator int().
    bool pcheck5 = pt11 == false;   // calls pimpl::op==() then pimpl::op bool()
    bool pcheck6 = pt11 != false;   // calls pimpl::op!=() then pimpl::op bool()
    bool pcheck7 = false == pt11;   // calls pimpl::op==() then pimpl::op bool()
    bool pcheck8 = false != pt11;   // calls pimpl::op!=() then pimpl::op bool()

    if ( pt11) foo = foo;            // calls conversion to bool.
    if (!pt11) foo = foo;            // calls conversion to bool.
    if ( vt11) foo = foo;            // calls conversion to bool.
    if (!vt11) foo = foo;            // calls conversion to bool.

    pt16.swap(pt17);              // Check swap() works.
//  vt16.swap(vt17);              // Check swap() works.

    int k11 = vt11.get(); assert(k11 ==  0);
    int k12 = vt12.get(); assert(k12 ==  5);
    int k13 = vt13.get(); assert(k13 ==  5);

    vt14.set(33);

    assert(vt12 == vt13); // Good: Only compiles if op==() is part of Test2 interface.
    assert(vt12 != vt11); // Good: Only compiles if op==() is part of Test2 interface.

    {
        Base        base1 (1);
        Derived1 derived1 (2, 3);
        Derived2 derived2 (2, 3, 4);
        Base        base2 (derived1); // calls copy copnstructor
        Base        base3 (derived2); // calls copy copnstructor
        Base        base4 (Derived2(2,3,4)/*const ref to temporary*/); // calls copy copnstructor
        Derived1     bad1 (null<Derived1>());
        Derived2     bad2 (null<Derived2>());
        Base*         bp1 = &base1;
        Base*         bp2 = &base2;
        Base*         bp3 = &base3;
        Base*         bp4 = &derived1;
        Base*         bp5 = &derived2;
        Base*         bp6 = &bad1;
        Base*         bp7 = &bad2;
        Base        bad_base1 = Base::null();
        Base        bad_base2 = null<Base>();
//      Base        bad_base3 = Base::null<Foo>(); // correctly does not compile.
//      Foo           bad_foo = null<Foo>(); // correctly does not compile.
        Derived1 bad_derived1 = null<Derived1>();
        Derived2 bad_derived2 = null<Derived2>();

        bool check1 = base1 == derived1;
        bool check2 = base1 == derived2;
        bool check3 = derived1 == base1;
        bool check4 = derived2 == base1;

        if ( bad1) printf("Bad\n");
        if (!bad2) printf("Good\n");

        base2.call_virtual(); // calls Derived1::call_virtual
        base3.call_virtual(); // calls Derived2::call_virtual

        bp1->call_virtual();    // calls Base::call_virtual
        bp2->call_virtual();    // calls Derived1::call_virtual
        bp3->call_virtual();    // calls Derived2::call_virtual
        bp4->call_virtual();    // calls Derived1::call_virtual
        bp5->call_virtual();    // calls Derived2::call_virtual
//      bp6->call_virtual();    // crash. referencing bad1
//      bp7->call_virtual();    // crash. referencing bad1
    }
    return 0;
}

