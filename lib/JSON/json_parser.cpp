#include "json_parser.h"
#include <fstream>
#include <sstream>
#include "json_printer.h"

bool JSON::charIsInString(char c, std::string str) {
    return str.find(c) != std::string::npos;
}

bool JSON::isWhiteSpace(char c) {
    // DANGER! Check for leading space to account for char ' '
    return charIsInString(c, " \t\n\f\r\v");
}

std::string JSON::parseString(std::string str, int& index) {
    std::string outString = "";
    index++;
    while (str[index] != '\"') {
        outString += str[index];
        index++;
    }
    return outString;
}

double JSON::parseNumerical(std::string str, int& index) {
    std::string tempStr = "";
    while (charIsInString(str[index], "-0123456789.") && index < str.size()) {
        tempStr += str[index];
        index++;
    }
    return std::stod(tempStr);
}

JSON::Data JSON::parseObject(JSON::Data& object, std::string& str, int& index) {
    bool haveKey = false;
    std::string key = "";
    std::string value = "";

    while (str[index] != '}' && index < str.size()) {
        if (charIsInString(str[index], "-0123456789.") && haveKey) {
            object[key] = parseNumerical(str, index);
            key = "";
            haveKey = false;
        }

        switch (str[index]) {
        case '{':
            if (haveKey) {
                JSON::Data nestedObject = JSON::Object{};
                object[key] = parseObject(nestedObject, str, ++index);
                haveKey = false;
                key = "";
            }
            else { object = parseObject(object, str, ++index); }
            break;
            // //         case '}': continue;
            // //         case '[': haveValue = false; break;
            // //         case ']': continue;

        case ':':
            if (!haveKey) { /* TODO: Throw an error */
            }
            break;

        case ',':
            if (!haveKey) { /* TODO: Throw an error */
            }
            haveKey = false;
            key = "";
            break;

        case '\"':
            if (!haveKey) {
                key = parseString(str, index);
                haveKey = true;
            }
            else {
                object[key] = parseString(str, index);
                key = "";  // reset the key
                haveKey = false;
            }
            break;

        case 't':
            if (haveKey) {
                object[key] = true;
                key = "";  // reset the key
                haveKey = false;
            }
            break;

        case 'f':
            if (haveKey) {
                object[key] = false;
                key = "";  // reset the key
                haveKey = false;
            }
            break;

        case 'n':
            if (haveKey) {
                object[key] = nullptr;
                key = "";  // reset the key
                haveKey = false;
            }
            break;

        default:
            break;
        }

        index++;
    }
    return object;
}

JSON::Data JSON::parse(std::string& jsonAsString) {
    JSON::Data object = JSON::Object{};
    int i = 0;

    while (isWhiteSpace(jsonAsString[i])) {
        if (i >= jsonAsString.size()) { break; }
        i++;
    }

    if (jsonAsString[i] != '{') { return JSON::Null{}; } /* TODO: throw or report an error */

    return parseObject(object, jsonAsString, ++i);
}

std::string JSON::readFile(const char* filepath) {
    std::ifstream file(filepath);
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

void JSON::saveFile(JSON::Data& data, const char* saveFilepath) {
    std::ofstream file(saveFilepath);
    file << JSON::prettyPrint(data);
    file.close();
}