#pragma once

#include "json_data.h"
#include <sstream>

namespace JSON {

    std::ostream& operator<<(std::ostream& os, Data const& d);

    std::string prettyPrint(Data const& data, int indent = 4);

}  // namespace JSON