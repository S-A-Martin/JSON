#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace JSON {
struct Null {};

std::ostream& operator<<(std::ostream& os, Null& n) {
  os << "null";
  return os;
}

class Data;  // forward declaration for JSON::Object and JSON::Array

using Object = std::map<std::string, Data>;
using Array = std::vector<Data>;

std::string types[] = {"JSON::Null",  "int",        "double",
                       "float",       "bool",       "JSON::Array",
                       "JSON::Array", "std::string"};

class Data {
  using JSONVariants =
      std::variant<Null, int, double, float, bool, Array, Object, std::string>;

 public:
  // assignment operator overload - for specific case
  Data& operator=(const char* t) {
    val = std::string(t);
    return *this;
  }

  // assignment operator overload - template for general cases
  template <typename T>
  Data& operator=(T t) {
    val = t;
    return *this;
  }

  // Constructors - for specific cases
  Data() : val(Null{}) {}
  Data(const char* t) : val(std::string{t}) {}

  // Constructors - template for general cases
  template <typename T>
  Data(T t) : val(t) {}

  // parenthesis operator overload
  JSONVariants& operator()() { return val; }

  // get wrapper
  template <typename T>
  T& Value() {
    return std::get<T>(val);
  }

  // index wrapper
  int Index() { return val.index(); }

 private:
  // Data members
  JSONVariants val;

};  // JSON::Data

};  // namespace JSON

using JSONFile = JSON::Object;

#endif  // JSON_H
