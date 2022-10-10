#pragma once

#include <sstream>
#include <fstream>

#include "json_data.h"

#define JSON_PRINT_INFO(X) std::cout << #X << " " << typeToString(X) << " = " << X << ";\n";

namespace JSON {

    std::string const typeToString(JSON::Data const& data);

}  // namespace JSON
