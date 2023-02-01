#pragma once

#include "json_data.h"

namespace JSON {

    Data parseFile(char const* path);

    void saveFile(Data const& data, char const* path);

};  // namespace JSON