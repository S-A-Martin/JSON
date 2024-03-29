#include "json_null.h"

namespace JSON {
    Null::Null() {}

    bool const Null::operator==(Null const& other) const {
        return true;
    }

    bool const Null::operator!=(Null const& other) const {
        return false;
    }
}  // namespace JSON