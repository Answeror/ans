#ifndef ANS_VAL_HPP
#define ANS_VAL_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

I am so awkward that I cannot find any implementation in boost that return value
its self while being a Polymorphic Function Object, i.e. can be used with
result_of.

I just want use this in

    generation(nonstop(val(1))) | taken(38)

to generate a range consists 38 ones.

In the document of fusion, it says:
"Boost.Lambda expressions don't work with __boost_result_of__"

So lambda cannot be used in oven.nonstop.

The actor in boost.phoneix is Polymorphic Function Object. But its assignment
operator is private, so it cannot be used with oven.taken.
--------------------------------------------------------------------------------
*/

namespace ans {

namespace functor {

template<class T>
struct val {
    typedef T result_type;
    T v;
    val(T v) : v(v) {}
    T operator ()() const { return v; }
}; // val

}

template<class T>
inline functor::val<T> val(T v) { return functor::val<T>(v); }

} // ans

#endif
