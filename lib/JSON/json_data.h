#pragma once

#include <iostream>
#include <variant>
#include <initializer_list>

#include "json_null.h"
#include "json_types.h"

namespace JSON {
    class Data {
      public:
        Value value;

        // Constructors
        Data();

        template <typename T>
        Data(T t);

        // Conversion Operators
        template <typename T>
        operator T();

        // Index Operator Overloads for Object
        Data& operator[](std::string const& key);
        Data& operator[](char const* key);

        // Index Operator Overload for Array
        Data& operator[](int const& elem);

        // Variant index wrapper
        int index() const;

        template <typename T>
        bool isType();

        template <typename T>
        bool operator==(T const& other) const;
        bool operator==(const char* other) const;

        template <typename T>
        bool operator!=(T const& other) const;
        bool operator!=(const char* other) const;

        size_t size();

        void clear();
    };  // class Data

};  // namespace JSON
