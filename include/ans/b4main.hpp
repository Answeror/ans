#if !defined(__B4MAIN_HPP_20111105115833__)
#define __B4MAIN_HPP_20111105115833__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-11-05
 *  
 *  @section DESCRIPTION
 *  
 * *
 */

namespace ans
{
    /**
     *  This class template is used to execute some function before main.
     *  
     *  Fn will be called during the instantiation of the default constructor of
     *  the template class.
     *  
     *  Example:
     *  <code>
     *  void foo()
     *  {
     *      // do something like registeration
     *  }
     *  namespace { const b4main<&foo> b4; }
     *  </code>
     */
    template<void(*Fn)()>
    struct b4main
    {
        b4main() { exec; }
        struct execute { execute() { Fn(); } };
        static execute exec;
    };

    template<void(*Fn)()> typename b4main<Fn>::execute b4main<Fn>::exec;
}

#endif // __B4MAIN_HPP_20111105115833__
