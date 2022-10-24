#include "json_printer.h"
#include <utility>

static int s_numTabs = 0;
static int s_tabWidth = 4;
static int s_numNewLines = 1;

namespace JSON {

    namespace {  // Annoymous to limit to json_printer.cpp

        std::string charRepeater(char c, int indexMax) {
            std::string str;
            for (int index = 0; index < indexMax; ++index) {
                str += c;
            }
            return str;
        }

        std::string prettyPrint(const std::pair<const std::string, Data> it, int numSpaces, int numNewLines) {
            return std::string("\"" + it.first + "\": " + prettyPrint(it.second, numSpaces, numNewLines));
        }

        template <typename T>
        std::string prettyPrintCollection(T const& collection, int numSpaces, int numNewLines, const char* brackets) {
            std::string str;
            str += brackets[0] + charRepeater('\n', s_numNewLines);
            ++s_numTabs;
            for (auto const& it : collection) {
                str += charRepeater(' ', s_numTabs * s_tabWidth) + prettyPrint(it, numSpaces, numNewLines);
                if (it != *std::prev(collection.end(), 1)) { str += ","; }  // if not the last collection element
                else if (s_tabWidth == 1) { str += " "; }                   // edge case for flat printing
                str += charRepeater('\n', s_numNewLines);
            }
            s_numTabs--;
            str += charRepeater(' ', s_numTabs * s_tabWidth) + brackets[1];
            return str;
        }

        template std::string prettyPrintCollection(Object const& collection, int numSpaces, int numNewLines, const char* brackets);
        template std::string prettyPrintCollection(Array const& collection, int numSpaces, int numNewLines, const char* brackets);

    }  // namespace

    std::ostream& operator<<(std::ostream& os, Data const& data) {
        switch (data.index()) {
        case Type::JSON_NULL:
            os << "null";
            break;
        case Type::INT:
            os << std::get<int>(data.value);
            break;
        case Type::UINT:
            os << std::get<unsigned int>(data.value);
            break;
        case Type::DOUBLE:
            os << std::get<double>(data.value);
            break;
        case Type::BOOL:
            os << (std::get<bool>(data.value) ? "true" : "false");
            break;
        case Type::STD_STRING:
            os << "\"" << std::get<std::string>(data.value) << "\"";
            break;
        case Type::JSON_OBJECT:
            os << prettyPrintCollection(std::get<Object>(data.value), s_tabWidth, s_numNewLines, "{}");
            break;
        case Type::JSON_ARRAY:
            os << prettyPrintCollection(std::get<Array>(data.value), s_tabWidth, s_numNewLines, "[]");
            break;
        }
        return os;
    }

    std::string prettyPrint(Data const& data, int numSpaces, int numNewLines) {
        s_tabWidth = numSpaces;
        s_numNewLines = numNewLines;
        std::stringstream ss;
        ss << data;
        return ss.str();
    }

    std::string print(Data const& data) {
        return prettyPrint(data, 1, 0);
    }

}  // namespace JSON
