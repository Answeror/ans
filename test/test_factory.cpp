#include <memory>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <ans/factory.hpp>
#include <ans/factory_impl.hpp>

struct base
{
    int x;
    base(int x) : x(x) {}
    virtual int f() const = 0;
};

typedef base * base_ptr;
typedef std::unique_ptr<base> unique_base_ptr;
typedef boost::shared_ptr<base> shared_base_ptr;

struct foo : base
{
    foo(int x) : base(x) {}
    int f() const { return x + 1; }
    static std::string identifier() { return "foo"; }

    void never_call_me()
    {
        ans::factory<base_ptr(int)>::register_product<foo>();
        ans::factory<unique_base_ptr(int)>::register_product<foo>();
        ans::factory<shared_base_ptr(int)>::register_product<foo>();
    }
};

struct bar : base
{
    bar(int x) : base(x) {}
    int f() const { return x + 2; }
    static std::string identifier() { return "bar"; }

    void never_call_me()
    {
        ans::factory<base_ptr(int)>::register_product<bar>();
        ans::factory<unique_base_ptr(int)>::register_product<bar>();
        ans::factory<shared_base_ptr(int)>::register_product<bar>();
    }
};

BOOST_AUTO_TEST_CASE(t_factory)
{
    auto &f = ans::factory<base_ptr(int)>::instance();
    auto p = f.make("foo")(0);
    auto q = f.make("bar")(0);
    BOOST_CHECK_EQUAL(p->f(), 1);
    BOOST_CHECK_EQUAL(q->f(), 2);
    delete p;
    delete q;
    BOOST_CHECK_EQUAL(ans::factory<unique_base_ptr(int)>::make("foo")(0)->f(), 1);
    BOOST_CHECK_EQUAL(ans::factory<unique_base_ptr(int)>::make("bar")(0)->f(), 2);
    BOOST_CHECK_EQUAL(ans::factory<shared_base_ptr(int)>::make("foo")(3)->f(), 4);
    BOOST_CHECK_EQUAL(ans::factory<shared_base_ptr(int)>::make("bar")(4)->f(), 6);
}
