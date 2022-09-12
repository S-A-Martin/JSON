#include "JSON/json.h"
#include "JSON/json_util.h"

/* JSON file to emulate
    {
      "integer test": 2147483647,
      "float test": 3.40282e+38,
      "double test": 1.79769e+308,
      "std::string test": "test string",
      "array test": [
                        "array element 0",
                        "array element 1"
                    ],
      "null test": null,
      "boolean test": true
   }
*/

JSONFile json_test = {
    {"integer test", std::numeric_limits<int>::max()},
    {"float test", std::numeric_limits<float>::max()},
    {"double test", std::numeric_limits<double>::max()},
    {"std::string test", {"test string"}},
    {"array test", JSON::Array{{"array element 0"}, {"array element 1"}}},
    {"null test", JSON::Null{}},
    {"boolean test", true}};

int main() {
  std::cout << "\n\nJSON data structure test: \n\n";

  JSONUtilities::Print<int>("integer test", json_test);
  JSONUtilities::Print<float>("float test", json_test);
  JSONUtilities::Print<double>("double test", json_test);
  JSONUtilities::Print<std::string>("std::string test", json_test);
  JSONUtilities::Print<bool>("boolean test", json_test);
  JSONUtilities::Print<std::string>("array test", json_test, 0);
  JSONUtilities::Print<std::string>("array test", json_test, 1);
  JSONUtilities::Print<JSON::Null>("null test", json_test);
  std::cout << "\n\n";

  return 0;
}
