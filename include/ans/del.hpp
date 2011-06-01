#ifndef ANS_DEL_HPP
#define ANS_DEL_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: deleter
--------------------------------------------------------------------------------
*/

namespace ans {

namespace detail
{
    struct none;
} // detail

template<class T = detail::none>
class del;

template<>
class del<detail::none>
{
public:
    template<class T>
    struct result;

    template<class T>
    struct result<del(T*)>
    {
        typedef void type;
    };

public:
    template<class T>
    void operator ()(T *p) const
    {
        delete p;
    }
}; // del

template<class T>
class del
{
public:
    template<class U>
    struct result;

    template<>
    struct result<del()>
    {
        typedef void type;
    };

public:
    del(T *p) : p(p) {}

public:
    void operator ()() const
    {
        delete p;
    }

private:
    T *p;
}; // del

} // ans

#endif ANS_DEL_HPP
