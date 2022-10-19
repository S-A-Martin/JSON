#pragma once

#include "json_data.h"
#include <sstream>

namespace JSON {

    extern int indentation;

    std::ostream& operator<<(std::ostream& os, JSON::Data const& d);
    std::string getInd(int indent);
    std::string prettyPrint(JSON::Data& data, int indent = 4);
    std::string prettyPrint(JSON::Array& array, int indent);

}  // namespace JSON