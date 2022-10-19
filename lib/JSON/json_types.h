#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include "json_null.h"

namespace JSON {

    // DANGER! For sanity, double check these
    // match the std::variant types in JSON::Data:value
    enum Type {
        JSON_NULL = 0,
        INT,
        UINT,
        DOUBLE,
        BOOL,
        STD_STRING,
        JSON_OBJECT,
        JSON_ARRAY,
        NUM_TYPES
    };

    class Data;  // to allow typedef of Object and Array containing Data
    typedef std::map<std::string, Data> Object;
    typedef std::vector<Data> Array;
    typedef std::variant<JSON::Null, int, unsigned int, double, bool, std::string, JSON::Object, JSON::Array> Value;

};  // namespace JSON