#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __METHOD_HPP_20111227141250__
#define __METHOD_HPP_20111227141250__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-27
 *  
 *  @section DESCRIPTION
 *  
 *  Example:
 *  @code
 *  // foo.hpp
 *  struct foo
 *  {
 *      void bar();
 *  };
 *  
 *  // foo.cpp
 *  namespace
 *  {
 *      struct foo_method : foo
 *      {
 *          void foobar() {}
 *      };
 *      ans::alpha::functional::method<foo_method> method;
 *  }
 *  
 *  void foo::bar()
 *  {
 *      method(this)->foobar();
 *  }
 *  @endcode
 */

#include <boost/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/implicit_cast.hpp>

namespace ans { namespace alpha {

    namespace functional
    {
        template<class T>
        struct method
        {
            typedef method this_type;

            template<class Base>
            const T* operator ()(const Base *p) const
            {
                static_assert(sizeof(T)==sizeof(Base), "T cannot have member variable.");
                static_assert(boost::is_base_of<Base, T>::value, "T must derived from Base.");
                BOOST_ASSERT(p);
                return static_cast<const T*>(p);
            }

            template<class Base>
            T* operator ()(Base *p) const
            {
                return const_cast<T*>((*this)(boost::implicit_cast<const Base*>(p)));
            }
        };
    }
}
}

#endif // __METHOD_HPP_20111227141250__
