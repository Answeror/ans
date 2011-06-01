#ifndef ANS_EXCEPTION_HPP
#define ANS_EXCEPTION_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 

TODO: this file shouldn't depend on check.hpp
--------------------------------------------------------------------------------
*/

#include "check.hpp"

namespace ans {

#define THROW_EXCEPTION(e)\
    ans::throw_exception(e,BOOST_CURRENT_FUNCTION,__FILE__,__LINE__)
#define MAKE_NESTED_EXCEPTION()\
    boost::enable_error_info(std::exception()) << boost::errinfo_nested_exception(boost::current_exception())

typedef boost::error_info<struct tag_msg, std::string> error_msg;

} // ans

#endif // ANS_EXCEPTION_HPP
