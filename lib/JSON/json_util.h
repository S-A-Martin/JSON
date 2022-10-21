#pragma once

#include <sstream>
#include <fstream>

#include "json_types.h"
#include "json_data.h"

#define JSON_PRINT_INFO(X) std::cout << #X << " " << typeToString(X) << " = " << X << ";\n";

namespace JSON {

    std::string const types[Type::NUM_TYPES] = { "JSON::Null", "int", "unsigned int", "double", "bool", "std::string", "JSON::Object", "JSON::Array" };

    std::string const typeToString(Data const& data);

}  // namespace JSON
