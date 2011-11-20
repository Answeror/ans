#pragma once

/*
--------------------------------------------------------------------------------
@author: answeror
@description: 
--------------------------------------------------------------------------------
*/

#include <memory>

namespace ans
{
    template<class Derived, class Elem>
    struct variant_visitor_base
    {
        virtual void operator ()(Elem) const {}
    };

    template<class Variant>
    struct variant_visitor;

    /// type erase base
    template<class Variant>
    struct variant_elem_base
    {
        virtual void apply_visitor(const variant_visitor<Variant> &visitor) const = 0;
    }

    /// type erase wrapper
    template<class Variant, class Elem>
    struct variant_elem_wrapper
    {
        Elem data;

        variant_elem_wrapper(Elem data) : data(data) {}

        void apply_visitor(const variant_visitor<Variant> &visitor) const
        {
            return visitor(data);
        }
    }

    template<class Variant>
    struct make_variant_elem_wrapper;

    template<class Variant>
    struct variant_base
    {
    public:
        typedef variant_elem_base<Variant> elem_type;
        typedef std::unique_ptr<elem_type> elem_ptr;

    public:
        template<class T>
        variant_base(T &&data) : m_data(make_variant_elem_wrapper<Variant>()()) {}

    private:
        elem_ptr m_data;
    };

    template<class Variant, int N>
    struct variant_elem_chain;

    /// used to identify chain end
    struct variant_elem_chain_end;
}

#define ANS_VARIANT_BEGIN(name)\
    #pragma push_macro("ANS_VARIANT_NAME")\
    #define ANS_VARIANT_NAME name\
    class name;\
    template<> struct ans::variant_elem_chain<name, __LINE__> : ans::variant_elem_chain_end {};
#define ANS_VARIANT_END() class ANS_VARIANT_NAME { typedef ans::variant_elem_chain<ANS_VARIANT_NAME, __LINE__ - 1> type; }; #pragma pop_macro("ANS_VARIANT_NAME");
#define ANS_VARIANT_ELEM(name) template<> struct ans::variant_elem_chain<ANS_VARIANT_NAME, __LINE__> : name, ans::variant_elem_chain<ANS_VARIANT_NAME, __LINE__ - 1> {};