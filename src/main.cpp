#include <iostream>
#include "json.h"

int main() {
    std::stringstream ss;
    JSON::Data data = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    ss << data;
    std::string expected =
        // clang-format off
R"({
    "Test String": 1,
    "Test String 2": 5.5,
    "Test String 3": true
})";
    // clang-format on
    std::cout << (ss.str() == expected ? "true" : "false");
    return 0;
}
