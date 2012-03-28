#if !defined(__MAKE_STRUCT_HPP_2011120404729__)
#define __MAKE_STRUCT_HPP_2011120404729__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-04
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#define BOOST_FUSION_INVOKE_MAX_ARITY 10
#include <boost/fusion/include/invoke.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace ans
{
    namespace bf = boost::fusion;
    
    namespace make_struct_detail
    {
        template<class T>
        struct make
        {
            /// zero argument
            T operator ()() const
            {
                return T();
            }

/// modify this number to provide more overloading            
#define ANS_MAKE_STRUCT_OVERLOAD_COUNT 10
#define ANS_MAKE_STRUCT_OVERLOAD(z, n, unused)\
            template<BOOST_PP_ENUM_PARAMS(n, class A)>\
            T operator ()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a)) const\
            {\
                T result = {BOOST_PP_ENUM_PARAMS(n, a)};\
                return result;\
            };

#define BOOST_PP_LOCAL_MACRO(n) ANS_MAKE_STRUCT_OVERLOAD(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (1, ANS_MAKE_STRUCT_OVERLOAD_COUNT - 1)
#include BOOST_PP_LOCAL_ITERATE()
#undef ANS_MAKE_STRUCT_OVERLOAD_COUNT
#undef ANS_MAKE_STRUCT_OVERLOAD

        };

        template<class Seq>
        struct struct_maker
        {
            Seq seq;

            struct_maker(const Seq &seq) : seq(seq) {}

            template<class T>
            operator T() const
            {
                return bf::invoke(make<T>(), seq);
            }
        };
    }

    /**
     *  @param seq fusion sequence
     *  @return an object can implicit cast to target struct
     */
    template<class Seq>
    inline make_struct_detail::struct_maker<Seq> make_struct(const Seq &seq)
    {
        return make_struct_detail::struct_maker<Seq>(seq);
    }
}

#endif // __MAKE_STRUCT_HPP_2011120404729__
