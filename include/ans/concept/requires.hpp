// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_REQUIRES_DWA2006430_HPP
# define BOOST_CONCEPT_REQUIRES_DWA2006430_HPP

# include <boost/config.hpp>
# include <boost/parameter/aux_/parenthesized_type.hpp>
# include <boost/concept/assert.hpp>
# include <boost/preprocessor/seq/for_each.hpp>

namespace boost { 

// Template for use in handwritten assertions
template <class Model, class More>
struct requires_ : More
{
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef typename More::type type;
# endif 
    BOOST_CONCEPT_ASSERT((Model));
};

// Template for use by macros, where models must be wrapped in parens.
// This isn't in namespace detail to keep extra cruft out of resulting
// error messages.
template <class ModelFn>
struct _requires_
{
    enum { value = 0 };
    BOOST_CONCEPT_ASSERT_FN(ModelFn);
};

template <int check, class Result>
struct Requires_ : ::boost::parameter::aux::unaryfunptr_arg_type<Result>
{
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef typename ::boost::parameter::aux::unaryfunptr_arg_type<Result>::type type;
# endif 
};

# if BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(1010))
#  define BOOST_CONCEPT_REQUIRES_(r,data,t) | (::boost::_requires_<void(*)t>::value)
# else 
#  define BOOST_CONCEPT_REQUIRES_(r,data,t) + (::boost::_requires_<void(*)t>::value)
# endif

#if defined(NDEBUG) || BOOST_WORKAROUND(BOOST_MSVC, < 1300)

# define BOOST_CONCEPT_REQUIRES(models, result)                                    \
    typename ::boost::parameter::aux::unaryfunptr_arg_type<void(*)result>::type

// Fix for forward declarations of template functions not working on MSVC when the  
// return type depends on complex types with non-type template arguments 
#elif BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600)) 
 
template <typename T1, typename T2> 
struct requires_msvc_workaround 
{ 
    typedef typename T2::type type; 
        enum{value = T1::value }; 
}; 
 
#define BOOST_CONCEPT_CLOSE_TEMPLATE(r, data, elem) > 
#define BOOST_CONCEPT_OPEN_TEMPLATE(r, data, elem)                                                              \ 
        ::boost::requires_msvc_workaround< ::boost::_requires_<void(*) elem > , 
 
#define BOOST_CONCEPT_REQUIRES(models , result)                                                                 \ 
    typename                                                                                                                                    \ 
    BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_OPEN_TEMPLATE, 0, models)                               \ 
        ::boost::parameter::aux::unaryfunptr_arg_type<void(*) result>                           \ 
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_CLOSE_TEMPLATE, 0, models)                          \ 
        ::type  

#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

// Same thing as below without the initial typename
# define BOOST_CONCEPT_REQUIRES(models, result)                                \
    ::boost::Requires_<                                                        \
      (0 BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_REQUIRES_, ~, models)),           \
      ::boost::parameter::aux::unaryfunptr_arg_type<void(*)result>          \
                     >::type

#else

// This just ICEs on MSVC6 :(
# define BOOST_CONCEPT_REQUIRES(models, result)                                        \
    typename ::boost::Requires_<                                                       \
      (0 BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_REQUIRES_, ~, models)),                   \
      void(*)result                                                                 \
    >::type

#endif 

// C++0x proposed syntax changed.  This supports an older usage
#define BOOST_CONCEPT_WHERE(models,result) BOOST_CONCEPT_REQUIRES(models,result)

} // namespace boost::concept_check

#endif // BOOST_CONCEPT_REQUIRES_DWA2006430_HPP