#pragma once

#include "json_data.h"

namespace JSON {
    bool charIsInString(char c, std::string str);

    bool isWhiteSpace(char c);

    std::string parseString(std::string str, int& index);

    double parseNumerical(std::string str, int& index);

    JSON::Data parseObject(JSON::Data& object, std::string& str, int& index);

    JSON::Data parse(std::string& str);

    std::string readFile(const char* path);

    void saveFile(JSON::Data& data, const char* path);

};  // namespace JSON