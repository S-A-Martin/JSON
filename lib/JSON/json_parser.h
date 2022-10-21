#pragma once

#include "json_data.h"

namespace JSON {

    std::string readFile(char const* path);

    Data parse(std::string const& str);

    void saveFile(Data const& data, char const* path);

};  // namespace JSON