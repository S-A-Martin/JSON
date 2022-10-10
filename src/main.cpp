#include <iostream>
#include <string>
#include "json.h"

int main() {
    std::string fileString = JSON::readFile("../example.json");
    JSON::Data json = JSON::parse(fileString);
    std::cout << json["product_info"]["title"] << '\n';
    std::cout << json["tracks"][2]["filename"] << '\n';
    return 0;
}