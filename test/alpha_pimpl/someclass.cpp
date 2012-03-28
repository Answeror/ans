/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-27
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <ans/alpha/pimpl.hpp>
#include <ans/alpha/pimpl_impl.hpp>
#include <ans/alpha/method.hpp>
#include "someclass.hpp"

namespace
{
    struct sm : someclass
    {
        int neg(int x) const
        {
            return -x;
        }
    };
    ans::alpha::functional::method<sm> method;
}

struct someclass::impl
{
    int x;
    impl(int x) : x(x) {}
};

someclass::someclass() : self(42)
{

}

someclass::~someclass()
{

}

int someclass::foo() const
{
    return method(this)->neg(self->x);
}
