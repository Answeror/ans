#if !defined(__IDENTIFIER_HPP_2011120200408__)
#define __IDENTIFIER_HPP_2011120200408__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-02
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

namespace ans
{
    /**
     *  A trait function to extract class identifier.
     *  
     *  Client need to either provide a static method named identifier or
     *  specialize this method.
     */
    template<class T>
    auto identifier() -> decltype(T::identifier())
    {
        return T::identifier();
    }
}

#endif // __IDENTIFIER_HPP_2011120200408__
