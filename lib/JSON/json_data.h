#pragma once

#include <iostream>
#include <variant>
#include "json_null.h"
#include "json_types.h"

namespace JSON {
    class Data {
      public:
        std::variant<JSON::Null, double, bool, JSON::Array, JSON::Object, std::string> value;

        // Constructors
        Data();
        Data(std::nullptr_t);
        Data(JSON::Null x);
        Data(int x);
        Data(double x);
        Data(float x);
        Data(bool x);
        Data(JSON::Array x);
        Data(JSON::Object x);
        Data(char const* x);
        Data(std::string x);

        // Conversion Operators
        operator Null();
        operator int();
        operator double();
        operator float();
        operator bool();
        operator Array();
        operator Object();
        operator std::string();

        // Index Operator Overload for Array
        Data& operator[](int const& elem);

        // Index Operator Overloads for Array
        Data& operator[](std::string const& key);
        Data& operator[](char const* key);

        // Variant index wrapper
        int const index() const;

        // Stream Operator Overload
        friend std::ostream& operator<<(std::ostream& os, JSON::Data const& d);

        bool operator==(JSON::Data const& other) const;
        bool operator!=(JSON::Data const& other) const;

        // bool operator==(JSON::Null const& null) const;
        // bool operator!=(JSON::Null const& null) const;
    };  // class Data
};      // namespace JSON
