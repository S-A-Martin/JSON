#pragma once

#include <map>
#include <vector>
#include <string>

namespace JSON {

    // DANGER! For sanity, double check these
    // match the std::variant types in JSON::Data:value
    enum Type {
        JSON_NULL = 0,
        DOUBLE,
        BOOL,
        JSON_ARRAY,
        JSON_OBJECT,
        STD_STRING
    };

    std::string const types[6] = { "JSON::Null", "double", "bool", "JSON::Array", "JSON::Object", "std::string" };

    class Data;  // to allow typedef of Object and Array containing Data
    typedef std::map<std::string, Data> Object;
    typedef std::vector<Data> Array;

};  // namespace JSON