#include "json_parser.h"
#include <fstream>
#include <sstream>
#include "json_printer.h"

#define JSON_DEBUG 0

#if JSON_DEBUG
    #define LOG(...) std::cout << __PRETTY_FUNCTION__ << " " << __VA_ARGS__ << std::endl;
#else
    #define LOG(...)
#endif

namespace JSON {

    namespace {  // Annoymous to limit to json_parser.cpp

        Data parseObject(Data& object, std::string const& str, int& index);

        bool charIsInString(char const c, std::string const& str) {
            return str.find(c) != std::string::npos;
        }

        bool isWhiteSpace(char const c) {
            // DANGER! Check for leading space to account for char ' '
            return charIsInString(c, " \t\n\f\r\v");
        }

        std::string parseString(std::string const& str, int& index) {
            std::string outString = "";
            ++index;
            while (str[index] != '\"' && index < str.size()) {
                LOG(str[index]);
                outString += str[index];
                ++index;
            }
            return outString;
        }

        Data parseNumerical(std::string const& str, int& index) {
            std::string tempStr = "";
            while (charIsInString(str[index], "-0123456789.") && index < str.size()) {
                LOG(str[index]);
                tempStr += str[index];
                ++index;
            }
            if (charIsInString('.', tempStr)) {
                return std::stod(tempStr);
            }
            return std::stoi(tempStr);
        }

        Data parseArray(Array& array, std::string const& str, int& index) {
            while (str[index] != ']' && index < str.size()) {
                LOG(str[index]);
                if (charIsInString(str[index], "-0123456789.")) {
                    array.push_back(parseNumerical(str, index));
                }
                switch (str[index]) {
                case '{': {
                    Data nestedObject = Object{};
                    array.push_back(parseObject(nestedObject, str, ++index));
                    break;
                }

                case '\"':
                    array.push_back(parseString(str, index));
                    break;

                case 't':
                    array.push_back(true);
                    break;

                case 'f':
                    array.push_back(false);
                    break;

                case 'n':
                    array.push_back(nullptr);
                    break;

                case '[': {
                    Array nestedArray;
                    array.push_back(parseArray(nestedArray, str, ++index));
                    break;
                }

                default:
                    break;
                }
                ++index;
            }
            return array;
        }

        Data parseObject(Data& object, std::string const& str, int& index) {
            bool haveKey = false;
            std::string key = "";

            while (str[index] != '}' && index < str.size()) {
                LOG(str[index]);
                if (charIsInString(str[index], "-0123456789.") && haveKey) {
                    object[key] = parseNumerical(str, index);
                    key = "";
                    haveKey = false;
                }

                switch (str[index]) {
                case '{':
                    if (haveKey) {
                        Data nestedObject = Object{};
                        object[key] = parseObject(nestedObject, str, ++index);
                        haveKey = false;
                        key = "";
                    }
                    else { object = parseObject(object, str, ++index); }
                    break;

                case '[':
                    if (haveKey) {
                        Array array;
                        object[key] = parseArray(array, str, ++index);
                        haveKey = false;
                        key = "";
                    }
                    // else { /* TODO: Throw an error */ }
                    break;

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

                ++index;
            }
            return object;
        }
    }  // namespace

    std::string readFile(const char* filepath) {
        std::ifstream file(filepath);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }

    Data parse(std::string const& jsonAsString) {
        Data object = Object{};
        int index = 0;
        LOG(jsonAsString[i]);

        while (isWhiteSpace(jsonAsString[index] && index < jsonAsString.size())) {
            index++;
            LOG(jsonAsString[i]);
        }

        if (jsonAsString[index] != '{') {
            return Null{};
        } /* TODO: throw or report an error */

        return parseObject(object, jsonAsString, ++index);
    }

    void saveFile(Data const& data, char const* saveFilepath) {
        std::ofstream file;
        file.open(saveFilepath, std::ofstream::out | std::ofstream::trunc);
        file << prettyPrint(data);
        file.close();
    }

}  // namespace JSON