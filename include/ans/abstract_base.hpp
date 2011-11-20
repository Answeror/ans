#ifndef ANS_ABSTRACT_HPP
#define ANS_ABSTRACT_HPP

namespace ans
{
    class abstract_base
    {
    protected:
        abstract_base() {}
        virtual ~abstract_base() = 0 {}
        abstract_base(const abstract_base &other) {}
        abstract_base & operator =(const abstract_base &other) { return *this; }
    };
}

#endif
