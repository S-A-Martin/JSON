#ifndef JSON_H
#define JSON_H

#include <map>       // std::map
#include <string>    // std::string
#include <variant>   // std::variant, std::get
#include <vector>    // std::vector
#include <iostream>  // std::ostream

/* Not to self I didn't that know overloaded constuctors took the place of overloaded assignment operators.
So:
int x = 55.f is copy constructor
but int x = 6; float y = 9.9f; x = y; is assignment operator.

Apparently if int had a constructor that took a float then we woulnd't need to define
and overload for operator =

The above could be lies. Find out more!


*/

namespace JSON {

    struct Null {
        friend bool operator==(const Null& lhs, const Null& rhs) { return true; }
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
        std::variant<Null, int, double, float, bool, Array, Object, std::string> value;

        Data() : value(Null{}) {}
        Data(std::nullptr_t) : value(Null{}) {}
        Data(Null x) : value(x) {}
        Data(int x) : value(x) {}
        Data(double x) : value(x) {}
        Data(float x) : value(x) {}
        Data(bool x) : value(x) {}
        Data(Array x) : value(x) {}
        Data(Object x) : value(x) {}
        Data(const char* x) : value(std::string(x)) {}
        Data(std::string x) : value(x) {}

        friend bool operator==(const Data& lhs, const Data& rhs) {
            return lhs.value == rhs.value;
        }

        // Conversion operator
        template <typename T>
        operator T() { return std::get<T>(value); }
    };  // class Data

    const std::string types[9] = { "JSON::Null", "int", "double", "float", "bool", "JSON::Array", "JSON::Object", "std::string" };

}  // namespace JSON

#endif  // JSON_H
