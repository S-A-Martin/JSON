#include "json_data.h"

// Constructors
JSON::Data::Data() : value(JSON::Null{}) {}
JSON::Data::Data(std::nullptr_t) : value(JSON::Null{}) {}
JSON::Data::Data(JSON::Null x) : value(x) {}
JSON::Data::Data(int x) : value((double)x) {}
JSON::Data::Data(double x) : value(x) {}
JSON::Data::Data(float x) : value((double)x) {}
JSON::Data::Data(bool x) : value(x) {}
JSON::Data::Data(JSON::Array x) : value(x) {}
JSON::Data::Data(JSON::Object x) : value(x) {}
JSON::Data::Data(char const* x) : value(std::string(x)) {}
JSON::Data::Data(std::string x) : value(x) {}

// Conversion JSON::Data::operators
JSON::Data::operator JSON::Null() { return std::get<JSON::Null>(value); }
JSON::Data::operator int() { return (int)(std::get<double>(value)); }
JSON::Data::operator double() { return std::get<double>(value); }
JSON::Data::operator float() { return (float)(std::get<double>(value)); }
JSON::Data::operator bool() { return std::get<bool>(value); }
JSON::Data::operator JSON::Array() { return std::get<JSON::Array>(value); }
JSON::Data::operator JSON::Object() { return std::get<JSON::Object>(value); }
JSON::Data::operator std::string() { return std::get<std::string>(value); }

// Square Bracket Overload for JSON::Array
JSON::Data& JSON::Data::operator[](int const& elem) {
    if (std::get_if<JSON::Array>(&value)) {
        return std::get<JSON::Array>(value)[elem];
    }
    return *this;
}

// Square Bracket Overloads for JSON::Array
JSON::Data& JSON::Data::operator[](std::string const& key) {
    if (std::get_if<JSON::Object>(&value)) {
        return std::get<JSON::Object>(value)[key];
    }
    return *this;
}

JSON::Data& JSON::Data::operator[](char const* key) {
    if (std::get_if<JSON::Object>(&value)) {
        return std::get<JSON::Object>(value)[key];
    }
    return *this;
}

// Variant index wrapper
int const JSON::Data::index() const { return value.index(); }

// Stream JSON::Data::operator Overload
std::ostream& JSON::operator<<(std::ostream& os, JSON::Data const& d) {
    // print if val is JSON::Null
    if (JSON::Null const* i = std::get_if<JSON::Null>(&d.value))
        os << "JSON::Null";

    // print if val is double
    if (double const* i = std::get_if<double>(&d.value))
        os << std::get<double>(d.value);

    // print if val is bool
    if (bool const* i = std::get_if<bool>(&d.value))
        os << (std::get<bool>(d.value) ? "true" : "false");

    // print if val is JSON::Array
    if (JSON::Array const* i = std::get_if<JSON::Array>(&d.value))
        os << "\"Invalid Output (JSON::Array)\"";

    // print if val is JSON::Object
    if (JSON::Object const* i = std::get_if<JSON::Object>(&d.value))
        os << "\"Invalid Output (JSON::Object)\"";

    // print if val is std::string
    if (std::string const* i = std::get_if<std::string>(&d.value))
        os << "\"" << std::get<std::string>(d.value) << "\"";

    return os;
}

// Equality JSON::Data::operator
bool JSON::Data::operator==(JSON::Data const& other) const {
    return value == other.value;
}
// Inequality JSON::Data::operator
bool JSON::Data::operator!=(JSON::Data const& other) const {
    return value != other.value;
}
// // Equality JSON::Data::operator with JSON::Null
// bool JSON::Data::operator==(JSON::Null const& null) const {
//     return std::get_if<JSON::Null>(&value) ? true : false;
// }
// // Inequality JSON::Data::operator with JSON::Null
// bool JSON::Data::operator!=(JSON::Null const& null) const {
//     return !std::get_if<JSON::Null>(&value) ? true : false;
// }
