#ifndef ANS_PARENTHESIS_AS_BRACKET_HPP
#define ANS_PARENTHESIS_AS_BRACKET_HPP

/*
--------------------------------------------------------------------------------
@author: answeror
@description: 用圆括号去调用方括号, 用于结合transformed实现as_indexed.
--------------------------------------------------------------------------------
*/

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
    #define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#include <boost/ref.hpp>
#include <boost/utility/declval.hpp>

namespace ans
{
    /// 没有result_type, 需要boost 1.47.0+.
    template<class T>
    class parenthesis_as_bracket
    {
    public:
        /// boost.transform_iterator有默认构造函数, 需要这个, 不知道为什么这样设计.
        parenthesis_as_bracket() {}

        parenthesis_as_bracket(T t) : data(t) {}

        //template<class Index>
        //decltype(boost::declval<T>()[boost::declval<Index>()]) operator ()(Index &&index)
        //{
        //    return data[std::forward<Index>(index)];
        //}

        template<class Index>
        decltype(boost::declval<const T>()[boost::declval<Index>()]) operator ()(Index &&index) const
        {
            return data[std::forward<Index>(index)];
        }

    private:
        T data;
    };

    template<class T>
    inline parenthesis_as_bracket<T> make_parenthesis_as_bracket(T t)
    {
        return parenthesis_as_bracket<T>(t);
    }

    /// 如果要使内部保存引用, 就用boost.ref.
    template<class T>
    inline parenthesis_as_bracket<T&> make_parenthesis_as_bracket(boost::reference_wrapper<T> t)
    {
        return parenthesis_as_bracket<T&>(t);
    }
}

#endif