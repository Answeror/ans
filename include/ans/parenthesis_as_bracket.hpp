#ifndef ANS_PARENTHESIS_AS_BRACKET_HPP
#define ANS_PARENTHESIS_AS_BRACKET_HPP

/*
--------------------------------------------------------------------------------
@author: answeror
@description: ��Բ����ȥ���÷�����, ���ڽ��transformedʵ��as_indexed.
--------------------------------------------------------------------------------
*/

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
    #define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#include <boost/ref.hpp>
#include <boost/utility/declval.hpp>

namespace ans
{
    /// û��result_type, ��Ҫboost 1.47.0+.
    template<class T>
    class parenthesis_as_bracket
    {
    public:
        /// boost.transform_iterator��Ĭ�Ϲ��캯��, ��Ҫ���, ��֪��Ϊʲô�������.
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

    /// ���Ҫʹ�ڲ���������, ����boost.ref.
    template<class T>
    inline parenthesis_as_bracket<T&> make_parenthesis_as_bracket(boost::reference_wrapper<T> t)
    {
        return parenthesis_as_bracket<T&>(t);
    }
}

#endif