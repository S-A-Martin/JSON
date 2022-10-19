#include "json_null.h"

JSON::Null::Null() {}

bool JSON::Null::operator==(JSON::Null const& other) const {
    return true;
}
// Inequality JSON::Data::operator
bool JSON::Null::operator!=(JSON::Null const& other) const {
    return false;
}