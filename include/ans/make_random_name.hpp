#ifndef ANS_MAKE_RANDOM_NAME_HPP
#define ANS_MAKE_RANDOM_NAME_HPP

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: Make a random name using boost::uuid.
--------------------------------------------------------------------------------
*/

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace ans {

inline std::string make_random_name() {
    return boost::lexical_cast<std::string>(
        boost::uuids::random_generator()()
    );
}

} // ans

#endif
