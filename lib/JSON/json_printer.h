#pragma once

#include "json_data.h"
#include <sstream>

namespace JSON {

    extern int indentation;

    std::string getInd(int indent);

    std::string prettyPrint(JSON::Data& data, int indent = 4);

    std::string prettyPrint(JSON::Array& array, int indent);

    std::string prettyPrint(JSON::Data& data, int indent);

    std::string prettyPrint(JSON::Array& array, int indent);
}  // namespace JSON