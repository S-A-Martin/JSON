#include "json_util.h"

namespace JSON {
    std::string const typeToString(Data const& data) { return { "<" + types[data.index()] + ">" }; }
}  // namespace JSON