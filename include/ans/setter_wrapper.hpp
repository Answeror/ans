#pragma once
#if !defined(__SETTER_WRAPPER_HPP_20111211142426__)
#define __SETTER_WRAPPER_HPP_20111211142426__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-11
 *  
 *  @section DESCRIPTION
 *  
 *  Used to wrapper Vector3's setX, setY, etc.
 */

namespace ans
{
    template<class Value, class Setter>
    class setter_wrapper
    {
    public:
        typedef Value value_type;
        typedef Setter setter_type;
        typedef setter_wrapper this_type;

    public:
        setter_wrapper(const Setter &setter) : setter(setter) {}

    public:
        void operator =(const value_type &value) const
        {
            setter(value);
        }

        void operator =(value_type &&value) const
        {
            setter(std::forward<value_type>(value));
        }

    private:
        Setter setter;
    };

    template<class Value, class Setter>
    inline setter_wrapper<Value, Setter> wrap_setter(const Setter &setter)
    {
        return setter_wrapper<Value, Setter>(setter);
    }
}

#endif // __SETTER_WRAPPER_HPP_20111211142426__
