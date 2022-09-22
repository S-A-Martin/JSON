#ifndef JSON_H
#define JSON_H

#include <map>       // std::map
#include <string>    // std::string
#include <variant>   // std::variant, std::get
#include <vector>    // std::vector
#include <iostream>  // std::ostream
#include <sstream>

/* Not to self I didn't that know overloaded constuctors took the place of overloaded assignment operators.
So:
int x = 55.f is copy constructor
but int x = 6; float y = 9.9f; x = y; is assignment operator.

Apparently if int had a constructor that took a float then we woulnd't need to define
and overload for operator =

The above could be lies. Find out more!


*/

#define JSON_PRINT_INFO(X) std::cout << #X << " " << JSON::typeToString(X) << " = " << X << ";\n";

namespace JSON {

    struct Null {};
    bool operator==(Null const& lhs, Null const& rhs) { return true; }

    class Data;  // Forward declare to allow typedef of Object and Array containing Data

    typedef std::map<std::string, Data> Object;
    typedef std::vector<Data> Array;
    typedef std::map<std::string, Data> File;

    class Data {
      public:
        std::variant<Null, int, double, float, bool, Array, Object, std::string> value;

        // Constructors
        Data() : value(Null{}) {}
        Data(std::nullptr_t) : value(Null{}) {}
        Data(Null x) : value(x) {}
        Data(int x) : value(x) {}
        Data(double x) : value(x) {}
        Data(float x) : value(x) {}
        Data(bool x) : value(x) {}
        Data(Array x) : value(x) {}
        Data(Object x) : value(x) {}
        Data(char const* x) : value(std::string(x)) {}
        Data(std::string x) : value(x) {}

        // Equality Operator
        friend bool operator==(Data const& lhs, Data const& rhs) {
            return lhs.value == rhs.value;
        }
        // Inequality Operator
        friend bool operator!=(Data const& lhs, Data const& rhs) {
            return lhs.value != rhs.value;
        }
        // Equality Operator with Null
        friend bool operator==(Data const& lhs, Null const& rhs) {
            return std::get_if<Null>(&lhs.value) ? true : false;
        }
        // Inequality Operator with Null
        friend bool operator!=(Data const& lhs, Null const& rhs) {
            return !std::get_if<Null>(&lhs.value) ? true : false;
        }

        // Conversion Operators
        operator Null() { return std::get<Null>(value); }
        operator int() { return std::get<int>(value); }
        operator double() { return std::get<double>(value); }
        operator float() { return std::get<float>(value); }
        operator bool() { return std::get<bool>(value); }
        operator Array() { return std::get<Array>(value); }
        operator Object() { return std::get<Object>(value); }
        operator std::string() { return std::get<std::string>(value); }

        // Square Bracket Overload for Array
        Data& operator[](int const& elem) {
            if (std::get_if<Array>(&value)) {
                return std::get<Array>(value)[elem];
            }
            return *this;
        }

        // Square Bracket Overloads for Array
        Data& operator[](std::string const& key) {
            if (std::get_if<Object>(&value)) {
                return std::get<Object>(value)[key];
            }
            return *this;
        }

        Data& operator[](char const* key) {
            if (std::get_if<Object>(&value)) {
                return std::get<Object>(value)[key];
            }
            return *this;
        }

        // Variant index wrapper
        int const index() const { return value.index(); }

        // Stream Operator Overload

        friend std::ostream& operator<<(std::ostream& os, Data const& d) {
            // print if val is Null
            if (Null const* i = std::get_if<Null>(&d.value))
                os << "null";

            // print if val is int
            if (int const* i = std::get_if<int>(&d.value))
                os << std::get<int>(d.value);

            // print if val is double
            if (double const* i = std::get_if<double>(&d.value))
                os << std::get<double>(d.value);

            // print if val is float
            if (float const* i = std::get_if<float>(&d.value))
                os << std::get<float>(d.value);

            // print if val is bool
            if (bool const* i = std::get_if<bool>(&d.value))
                os << (std::get<bool>(d.value) ? "true" : "false");

            // print if val is Array
            if (Array const* i = std::get_if<Array>(&d.value))
                os << "\"Invalid Output (JSON::Array)\"";

            // print if val is Object
            if (Object const* i = std::get_if<Object>(&d.value))
                os << "\"Invalid Output (JSON::Object)\"";

            // print if val is std::string
            if (std::string const* i = std::get_if<std::string>(&d.value))
                os << "\"" << std::get<std::string>(d.value) << "\"";

            return os;
        }

    };  // class Data

    std::string const types[9] = { "JSON::Null", "int", "double", "float", "bool", "JSON::Array", "JSON::Object", "std::string" };
    std::string const typeToString(Data const& data) { return { "<" + types[data.index()] + ">" }; }

    int indentation = 1;

    std::string getInd(int indent) {
        std::string spaces;
        for (int i = 0; i < indentation * indent; i++) {
            spaces += " ";
        }
        return spaces;
    }

    std::string prettyPrint(Array& array, int indent);

    std::string prettyPrint(Data& data, int indent) {
        std::stringstream ss;
        if (data.index() == 6) {
            ss << "{\n";
            indentation++;
            // iterate and print map
            File::iterator it;
            Object object = std::get<Object>(data.value);
            for (it = object.begin(); it != object.end(); it++) {
                ss << getInd(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
                if (it != std::prev(object.end(), 1)) { ss << ","; }
                ss << '\n';
            }
            indentation--;
            ss << getInd(indent) << "}";
        }

        else if (data.index() == 5) { ss << prettyPrint(std::get<Array>(data.value), indent); }
        else { ss << data; }
        return ss.str();
    }

    std::string prettyPrint(Array& array, int indent) {
        std::stringstream ss;
        ss << "[\n";
        indentation++;
        for (int i = 0; i < array.size(); i++) {
            ss << getInd(indent) << prettyPrint(array[i], indent);
            if (i != array.size() - 1) { ss << ","; }
            ss << '\n';
        }
        indentation--;
        ss << getInd(indent) << "]";
        return ss.str();
    }

    std::string prettyPrint(File& file, int indent = 4) {
        std::stringstream ss;
        ss << "{\n";
        // iterate and print map
        File::iterator it;
        for (it = file.begin(); it != file.end(); it++) {
            ss << getInd(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
            if (it != std::prev(file.end(), 1)) { ss << ","; }
            ss << '\n';
        }
        indentation--;
        ss << getInd(indent) << "}";
        return ss.str();
    }
}  // namespace JSON

#endif  // JSON_H