#include "json_null.h"

bool JSON::Null::operator==(JSON::Null const& other) const { return true; }
bool JSON::Null::operator!=(JSON::Null const& other) const { return false; }