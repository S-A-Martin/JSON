#include "json_util.h"

std::string const JSON::typeToString(JSON::Data const& data) { return { "<" + types[data.index()] + ">" }; }


