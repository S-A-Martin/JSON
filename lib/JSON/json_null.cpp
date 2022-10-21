#include "json_null.h"

JSON::Null::Null() {}

bool const JSON::Null::operator==(JSON::Null const& other) const {
    return true;
}
// Inequality JSON::Data::operator
bool const JSON::Null::operator!=(JSON::Null const& other) const {
    return false;
}