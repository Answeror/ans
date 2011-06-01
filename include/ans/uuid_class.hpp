#ifndef ANS_UUID_CLASS_HPP
#define ANS_UUID_CLASS_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace ans {

class uuid_class : public boost::uuids::uuid {
public:
    struct uuid_extractor {
        const boost::uuids::uuid & operator ()(const boost::uuids::uuid &arg) {
            return arg;
        }
    };
public:
    uuid_class() : boost::uuids::uuid(boost::uuids::random_generator()()) {}
    explicit uuid_class(boost::uuids::uuid const& u) : boost::uuids::uuid(u) {}
public:
    const boost::uuids::uuid & uuid() const {
        return static_cast<const boost::uuids::uuid&>(*this);
    }
};

} // ans

#endif
