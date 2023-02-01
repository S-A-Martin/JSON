#include "json_data.h"

namespace JSON {

    Data::Data() : value(Null{}) {}

    template <typename T>
    Data::Data(T t) : value(t) {}

    template Data::Data(Null t);
    template Data::Data(int t);
    template Data::Data(unsigned int t);
    template Data::Data(double t);
    template Data::Data(bool t);
    template Data::Data(std::string t);
    template Data::Data(Object t);
    template Data::Data(Array t);

    template <>
    Data::Data(std::nullptr_t) : value(Null{}) {}
    template <>
    Data::Data(float t) : value(double(t)) {}
    template <>
    Data::Data(char const* t) : value(std::string(t)) {}

    template <typename T>
    Data::Data(std::vector<T> vector) {
        value = JSON::Array{};
        for (auto s : vector) {
            std::get<Array>(value).push_back(JSON::Data{ s });
        }
    }

    template Data::Data(std::vector<Null>);
    template Data::Data(std::vector<int>);
    template Data::Data(std::vector<unsigned int>);
    template Data::Data(std::vector<double>);
    // std::vector<bool> missing as the STL has specialised it for another use
    template Data::Data(std::vector<std::string>);
    template Data::Data(std::vector<Object>);
    template Data::Data(std::vector<Array>);

    // Conversion Data::operators
    template <typename T>
    Data::operator T() { return std::get<T>(value); }

    template Data::operator Null();
    template Data::operator int();
    template Data::operator unsigned int();
    template Data::operator double();
    template Data::operator bool();
    template Data::operator std::string();
    template Data::operator Object();
    template Data::operator Array();

    template <>
    Data::operator float() { return (float)std::get<double>(value); }

    template <typename T>
    Data::operator std::vector<T>() {
        std::vector<T> vec;
        for (auto& s : std::get<Array>(value)) {
            vec.push_back(s);
        }
        return vec;
    }

    template Data::operator std::vector<int>();
    template Data::operator std::vector<unsigned int>();
    template Data::operator std::vector<double>();
    // std::vector<bool> missing as the STL has specialised it for another use
    template Data::operator std::vector<std::string>();
    template Data::operator std::vector<JSON::Object>();
    template Data::operator std::vector<JSON::Array>();

    // Square Bracket Overloads for Object
    Data const& Data::operator[](std::string const& key) const {
        if (const Object* object = std::get_if<Object>(&value)) {
            return (*object).at(key);
        }
        return *this;
    }

    Data& Data::operator[](std::string const& key) {
        if (Object* object = std::get_if<Object>(&value)) {
            return (*object)[key];
        }
        return *this;
    }

    Data const& Data::operator[](char const* key) const {
        if (const Object* object = std::get_if<Object>(&value)) {
            return (*object).at(key);
        }
        return *this;
    }

    Data& Data::operator[](char const* key) {
        if (Object* object = std::get_if<Object>(&value)) {
            return (*object)[key];
        }
        return *this;
    }

    // Square Bracket Overload for Array
    Data const& Data::operator[](int const& elem) const {
        if (const Array* array = std::get_if<Array>(&value)) {
            return (*array)[elem];
        }
        return *this;
    }

    Data& Data::operator[](int const& elem) {
        if (Array* array = std::get_if<Array>(&value)) {
            return (*array)[elem];
        }
        return *this;
    }

    // Variant index wrapper
    int Data::index() const { return value.index(); }

    template <typename T>
    bool Data::isType() const { return (std::get_if<T>(&value) != nullptr); }

    template bool Data::isType<Null>() const;
    template bool Data::isType<int>() const;
    template bool Data::isType<unsigned int>() const;
    template bool Data::isType<double>() const;
    template bool Data::isType<bool>() const;
    template bool Data::isType<std::string>() const;
    template bool Data::isType<Object>() const;
    template bool Data::isType<Array>() const;

    template <typename T>
    bool Data::operator==(T const& other) const {
        if (const T* ptr = std::get_if<T>(&value)) {
            return *ptr == other;
        }

        return false;
    }

    template bool Data::operator==(Null const& other) const;
    template bool Data::operator==(int const& other) const;
    template bool Data::operator==(unsigned int const& other) const;
    template bool Data::operator==(double const& other) const;
    template bool Data::operator==(bool const& other) const;
    template bool Data::operator==(std::string const& other) const;
    template bool Data::operator==(Object const& other) const;
    template bool Data::operator==(Array const& other) const;

    template <>
    bool Data::operator==(Data const& other) const {
        return this->value == other.value;
    }

    template <>
    bool Data::operator==(std::nullptr_t const& other) const {
        return std::get_if<Null>(&value);
    }

    bool Data::operator==(char const* other) const {
        if (const std::string* ptr = std::get_if<std::string>(&value)) {
            return strcmp(ptr->c_str(), other) == 0;
        }

        return false;
    }

    template <typename T>
    bool Data::operator!=(T const& other) const {
        return !operator==(other);
    }

    template bool Data::operator!=(Null const& other) const;
    template bool Data::operator!=(int const& other) const;
    template bool Data::operator!=(unsigned int const& other) const;
    template bool Data::operator!=(double const& other) const;
    template bool Data::operator!=(bool const& other) const;
    template bool Data::operator!=(std::string const& other) const;
    template bool Data::operator!=(Object const& other) const;
    template bool Data::operator!=(Array const& other) const;
    template bool Data::operator!=(Data const& other) const;

    bool Data::operator!=(char const* other) const {
        return !operator==(other);
    }

    size_t Data::size() const {
        switch (value.index()) {
        case Type::JSON_OBJECT:
        case Type::JSON_ARRAY:
            return sumCollectionSize(*this);
            break;

        case Type::INT:
        case Type::UINT:
        case Type::BOOL:
        case Type::DOUBLE:
        case Type::STD_STRING:
            return 1;
            break;

        case Type::JSON_NULL:
        default:
            return 0;
        }
    }

    int Data::sumCollectionSize(Data const& data) const {
        /* Recursively sums the size of the current Object (a.k.a std::map)
           or Array (a.k.a std::vector) with the sum of any nested Objects or Arrays.
        */

        int sumSize = 0;

        if (data.index() == Type::JSON_OBJECT) {
            Object const& object = std::get<Object>(data.value);
            for (auto const& [mapKey, mapValue] : object) {
                sumSize += sumCollectionSize(mapValue);
            }
            sumSize += object.size();  // object.size() a.k.a std::map::size();
        }
        else if (data.index() == Type::JSON_ARRAY) {
            Array const& array = std::get<Array>(data.value);
            for (auto const& arrValue : array) {
                sumSize += sumCollectionSize(arrValue);
            }
            sumSize += array.size();  // array.size() a.k.a std::vector::size();
        }

        return sumSize;
    }

    void Data::clear() {
        value = Null{};
    }

}  // namespace JSON