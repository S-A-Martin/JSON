#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include <iostream>
#include <limits>

namespace JSONUtilities {

// const int INT_MIN = std::numeric_limits<int>::min();

void PrintKey(std::string str) { std::cout << "\"" << str + "\" "; }

void Print_type(std::string str, JSON::Object o) {
  std::cout << "<" << JSON::types[o[str].Index()] << "> ";
}

template <typename T>
void PrintValue(std::string str, JSON::Object o, int elem = INT_MIN) {
  if (elem == INT_MIN) {
    std::cout << o[str].Value<T>();
  } else {
    if (o[str].Value<JSON::Array>().size() == 0 ||  // Array is empty
        elem < 0 ||  // trying to access a negative Array element
        elem > o[str].Value<JSON::Array>().size() -
                   1) {  // trying to access above Array size
      std::cout << "Array access out of bounds or empty";
      return;
    }
    std::cout << "[" << elem << "] "
              << (o[str].Value<JSON::Array>()[elem].Value<T>());
  }
}

template <>
void PrintValue<bool>(std::string str, JSON::Object o, int elem) {
  std::cout << (o[str].Value<bool>() ? "true" : "false");
}

template <>
void PrintValue<JSON::Null>(std::string str, JSON::Object o, int elem) {
  std::cout << o[str].Value<JSON::Null>();
}

template <typename T>
void Print(std::string str, JSON::Object o, int elem = INT_MIN) {
  PrintKey(str);
  Print_type(str, o);
  std::cout << "= ";
  PrintValue<T>(str, o, elem);
  std::cout << '\n';
}

};  // namespace JSONUtilities

#endif  // JSON_UTIL_H