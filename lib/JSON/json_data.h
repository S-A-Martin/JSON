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
        Data const& operator[](std::string const& key) const;
        Data& operator[](std::string const& key);
        Data const& operator[](char const* key) const;
        Data& operator[](char const* key);

        // Index Operator Overload for Array
        Data const& operator[](int const& elem) const;
        Data& operator[](int const& elem);

        // Variant index wrapper
        int const index() const;

        template <typename T>
        bool isType() const;

        template <typename T>
        bool operator==(T const& other) const;
        bool operator==(char const* other) const;

        template <typename T>
        bool operator!=(T const& other) const;
        bool operator!=(char const* other) const;

        size_t const size() const;

        void clear();

      private:
        int const sumCollectionSize(Data const&) const;

    };  // class Data

};  // namespace JSON
