#pragma once

#include "json_data.h"

namespace JSON {

    std::string readFile(const char* path);

    JSON::Data parse(std::string& str);

    void saveFile(JSON::Data& data, const char* path);

};  // namespace JSON