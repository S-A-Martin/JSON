#ifndef JSON_H
#define JSON_H

#include <map>       // std::map
#include <string>    // std::string
#include <variant>   // std::variant, std::monostate, std::get
#include <vector>    // std::vector
#include <iostream>  // std::ostream

namespace JSON {

    struct Null {
        friend bool operator==(const Null& lhs, const Null& rhs) { return true; }
        friend bool operator!=(const Null& lhs, const Null& rhs) { return false; }
        friend std::ostream& operator<<(std::ostream& os, const Null& n) {
            os << "null";
            return os;
        }
    };

    class Data;  // Forward declare to allow typedef of Object and Array containing Data

    typedef std::map<std::string, Data> Object;
    typedef std::vector<Data> Array;
    typedef std::map<std::string, Data> File;

    class Data {
      public:
        std::variant<std::monostate, Null, int, double, float, bool, Array, Object, std::string> value;

        Data() : value(Null{}) {}
    };  // class Data

    const std::string types[9] = { "std::monostate", "JSON::Null", "int", "double", "float", "bool", "JSON::Array", "JSON::Object", "std::string" };

}  // namespace JSON

#endif  // JSON_H
