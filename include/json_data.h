#pragma once

#include "json_null.h"
#include "json_types.h"

namespace JSON {
    class Data {
        // General info: JSON::Data is essentially a convenience API wrapping a Value a.k.a std::variant with the correct data types
        // allowed in JSON such as: JSON::Null, int, unsigned int, double, bool, std::string, JSON::Object, JSON::Array
        // Templates are used in a few places to keep the API looking clean and clear but implementation files limit the available template
        // parameters to the std::variant types mentioned above.

      public:
        Value value;

        // Default Constructor will set 'Data::value' type to JSON::Null
        Data();

        // Calling the constuctor with one of the available types will set 'Data::value' to be a copy of the passed in parameter (and set it to the same type)
        template <typename T>
        Data(T t);

        // Conversion operator gets the value stored in 'Data::value' allowing code such as 'Data json(150); int num = json;' (when 'Data::value' is an int)
        template <typename T>
        operator T();

        template <typename T>
        Data(std::vector<T>);

        template <typename T>
        operator std::vector<T>();

        // Allows std::string based access to the contents of 'Data::value' if 'Data::value' is a JSON::Object (a.k.a std::map<std::string, JSON::Data>) if not, returns a reference to itself
        Data const& operator[](std::string const& key) const;
        Data& operator[](std::string const& key);
        Data const& operator[](char const* key) const;
        Data& operator[](char const* key);

        // Allows indexing access of 'Data::value' if 'Data::value' is a JSON::Array (a.k.a std::vector<JSON::Data>) if not, returns a reference to itself
        Data const& operator[](int const& elem) const;
        Data& operator[](int const& elem);

        // Returns the type index of 'Data::value'
        int index() const;

        // Returns true if the type of 'Data::value' matches the template parameter. Usage: JSON::Data json(5.5); bool matches = json.isType<double>();
        template <typename T>
        bool isType() const;

        template <typename T>
        bool operator==(T const& other) const;
        bool operator==(char const* other) const;

        template <typename T>
        bool operator!=(T const& other) const;
        bool operator!=(char const* other) const;

        size_t size() const;

        void clear();

      private:
        int sumCollectionSize(Data const&) const;

    };  // class Data

};  // namespace JSON
