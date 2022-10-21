#include "json_data.h"

// Constructors
JSON::Data::Data() : value(JSON::Null{}) {}

template <typename T>
JSON::Data::Data(T t) : value(t) {}

template JSON::Data::Data(JSON::Null t);
template JSON::Data::Data(int t);
template JSON::Data::Data(unsigned int t);
template JSON::Data::Data(double t);
template JSON::Data::Data(bool t);
template JSON::Data::Data(std::string t);
template JSON::Data::Data(JSON::Object t);
template JSON::Data::Data(JSON::Array t);

template <>
JSON::Data::Data(std::nullptr_t) : value(JSON::Null{}) {}
template <>
JSON::Data::Data(float t) : value(double(t)) {}
template <>
JSON::Data::Data(char const* t) : value(std::string(t)) {}

// Conversion JSON::Data::operators
template <typename T>
JSON::Data::operator T() { return std::get<T>(value); }

template JSON::Data::operator JSON::Null();
template JSON::Data::operator int();
template JSON::Data::operator unsigned int();
template JSON::Data::operator double();
template JSON::Data::operator bool();
template JSON::Data::operator std::string();
template JSON::Data::operator JSON::Object();
template JSON::Data::operator JSON::Array();

template <>
JSON::Data::operator float() { return (float)std::get<double>(value); }

// Square Bracket Overloads for JSON::Object
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

// Square Bracket Overload for JSON::Array
JSON::Data& JSON::Data::operator[](int const& elem) {
    if (std::get_if<JSON::Array>(&value)) {
        return std::get<JSON::Array>(value)[elem];
    }
    return *this;
}

// Variant index wrapper
int JSON::Data::index() const { return value.index(); }

template <typename T>
bool JSON::Data::isType() { return (std::get_if<T>(&value) != nullptr); }

template bool JSON::Data::isType<JSON::Null>();
template bool JSON::Data::isType<int>();
template bool JSON::Data::isType<unsigned int>();
template bool JSON::Data::isType<double>();
template bool JSON::Data::isType<bool>();
template bool JSON::Data::isType<std::string>();
template bool JSON::Data::isType<JSON::Object>();
template bool JSON::Data::isType<JSON::Array>();

template <typename T>
bool JSON::Data::operator==(T const& other) const {
    if (const T* ptr = std::get_if<T>(&value)) {
        return *ptr == other;
    }

    return false;
}

template bool JSON::Data::operator==(JSON::Null const& other) const;
template bool JSON::Data::operator==(int const& other) const;
template bool JSON::Data::operator==(unsigned int const& other) const;
template bool JSON::Data::operator==(double const& other) const;
template bool JSON::Data::operator==(bool const& other) const;
template bool JSON::Data::operator==(std::string const& other) const;
template bool JSON::Data::operator==(JSON::Object const& other) const;
template bool JSON::Data::operator==(JSON::Array const& other) const;

template <>
bool JSON::Data::operator==(JSON::Data const& other) const {
    return this->value == other.value;
}

template <>
bool JSON::Data::operator==(std::nullptr_t const& other) const {
    return std::get_if<JSON::Null>(&value);
}

bool JSON::Data::operator==(char const* other) const {
    if (const std::string* ptr = std::get_if<std::string>(&value)) {
        return strcmp(ptr->c_str(), other) == 0;
    }

    return false;
}

template <typename T>
bool JSON::Data::operator!=(T const& other) const {
    return !operator==(other);
}

template bool JSON::Data::operator!=(JSON::Null const& other) const;
template bool JSON::Data::operator!=(int const& other) const;
template bool JSON::Data::operator!=(unsigned int const& other) const;
template bool JSON::Data::operator!=(double const& other) const;
template bool JSON::Data::operator!=(bool const& other) const;
template bool JSON::Data::operator!=(std::string const& other) const;
template bool JSON::Data::operator!=(JSON::Object const& other) const;
template bool JSON::Data::operator!=(JSON::Array const& other) const;
template bool JSON::Data::operator!=(JSON::Data const& other) const;

bool JSON::Data::operator!=(char const* other) const {
    return !operator==(other);
}

size_t JSON::Data::size() {
    switch (value.index()) {
    case JSON::Type::JSON_OBJECT:
    case JSON::Type::JSON_ARRAY:
        return sumCollectionSize(*this);
        break;

    case JSON::Type::INT:
    case JSON::Type::UINT:
    case JSON::Type::BOOL:
    case JSON::Type::DOUBLE:
    case JSON::Type::STD_STRING:
        return 1;
        break;

    case JSON::Type::JSON_NULL:
    default:
        return 0;
    }
}

int JSON::Data::sumCollectionSize(JSON::Data& data) {
    /* Recursively sums the size of the current JSON::Object (a.k.a std::map)
       or JSON::Array (a.k.a std::vector) with the sum of any nested Objects or Arrays.
    */

    int sumSize = 0;

    if (data.index() == JSON::Type::JSON_OBJECT) {
        JSON::Object& object = std::get<JSON::Object>(data.value);
        for (auto& [mapKey, mapValue] : object) {
            sumSize += sumCollectionSize(mapValue);
        }
        sumSize += object.size();  // object.size() a.k.a std::map::size();
    }
    else if (data.index() == JSON::Type::JSON_ARRAY) {
        JSON::Array& array = std::get<JSON::Array>(data.value);
        for (auto& arrValue : array) {
            sumSize += sumCollectionSize(arrValue);
        }
        sumSize += array.size();  // array.size() a.k.a std::vector::size();
    }

    return sumSize;
}

void JSON::Data::clear() {
    value = JSON::Null{};
}
