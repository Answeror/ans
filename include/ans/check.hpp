#ifndef ANS_CHECK_HPP
#define ANS_CHECK_HPP

/*
@author: Answeror
@description:
*/

#include <cassert>
#include <string>
#include <stdexcept>
#include <boost/exception/all.hpp>

namespace ans {

// Utility to generate string of condition.
#ifndef MAKE_ERROR_INFO
    #define MAKE_ERROR_INFO(condition) (condition), #condition
#endif

// Utility to check a condition.
//#ifndef CHECK
//    #define CHECK(exception, condition)\
//        ans::check<exception>(MAKE_ERROR_INFO(condition))
//#endif

typedef boost::error_info<struct stack_trace_, std::string> stack_trace;

inline std::string make_one_level_stack_trace(
    const char *fn,
    const char *file,
    int line
) {
    using namespace std;
    ostringstream oss;
    oss << string(80, '-')
        << "function: " << fn << '\n'
        << "file: " << file << '\n'
        << "line: " << line << '\n';
    return oss.str();
}

template<class E>
inline void throw_exception(
    const E &x, 
    const char *fn,
    const char *file,
    int line
) {
    boost::throw_exception(
        boost::exception_detail::set_info(
            boost::exception_detail::set_info(
                boost::exception_detail::set_info(
                    boost::exception_detail::set_info(
                        boost::enable_error_info(x),
                        stack_trace(make_one_level_stack_trace(fn, file, line))
                    ),
                    boost::throw_function(fn)
                ),
                boost::throw_file(file)
            ),
            boost::throw_line(line)
        )
    );
}

#define CHECK(exception, condition)\
    if (!(condition)) ans::throw_exception(exception(#condition),BOOST_CURRENT_FUNCTION,__FILE__,__LINE__)

#define GET_STACK_TRACE(e) (boost::get_error_info<ans::stack_trace>(e) ? *boost::get_error_info<ans::stack_trace>(e) : "")
#define APPEND_STACK_TRACE(e) e << ans::stack_trace(GET_STACK_TRACE(e) + ans::make_one_level_stack_trace(BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

// Check condition and may throw exception.
template<class Exception>
inline void check(bool condition) {
    if (!condition) {
        throw Exception();
    }
}

// Check condition and may throw exception with one argument.
template<class Exception, class Arg1>
inline void check(bool condition, Arg1 arg1) {
    if (!condition) {
        throw Exception(arg1);
    }
}

// A safer assert, remain valid in release version.
inline void assertion(bool condition) {
    assert(condition);
    check<std::logic_error>(condition, "Assert failed.");
}

} // ans

#endif
