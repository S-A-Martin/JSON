#pragma once

#include "json_data.h"

namespace JSON {

    std::string readFile(char const* path);

    JSON::Data parse(std::string const& str);

    void saveFile(JSON::Data const& data, char const* path);

};  // namespace JSON