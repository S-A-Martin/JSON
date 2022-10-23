#include "json_printer.h"

static int indentWidth = 0;

namespace JSON {

    namespace {  // Annoymous to limit to json_printer.cpp
        std::string getIndentation(int indent) {
            std::string spaces;
            for (int index = 0; index < indentWidth * indent; ++index) {
                spaces += " ";
            }
            return spaces;
        }

        std::string getNewLines(int numNewLines) {
            std::string newLines;
            for (int index = 0; index < numNewLines; ++index) {
                newLines += '\n';
            }
            return newLines;
        }
    }  // namespace

    // Stream Data::operator Overload
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
            os << prettyPrint(data);
            break;
        case Type::JSON_ARRAY:
            os << print(data);
            break;
        }

        return os;
    }

    std::string prettyPrint(Data const& data, int indent, int newLines) {
        std::stringstream ss;

        if (data.index() == JSON_OBJECT) {
            Object const object = std::get<Object>(data.value);
            ss << "{" << getNewLines(newLines);
            ++indentWidth;
            Object::const_iterator it;
            for (it = object.begin(); it != object.end(); ++it) {
                ss << getIndentation(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
                if (it != std::prev(object.end(), 1)) { ss << ","; }
                else if (indent == 1) { ss << " "; }  // edge case for flat printing
                ss << getNewLines(newLines);
            }
            indentWidth--;
            ss << getIndentation(indent) << "}";
        }

        else if (data.index() == JSON_ARRAY) {
            Array const array = std::get<Array>(data.value);
            ss << "[" << getNewLines(newLines);
            ++indentWidth;
            for (int index = 0; index < array.size(); ++index) {
                ss << getIndentation(indent) << prettyPrint(array[index], indent);
                if (index != array.size() - 1) { ss << ","; }
                else if (indent == 1) { ss << " "; }  // edge case for flat printing
                ss << getNewLines(newLines);
            }
            indentWidth--;
            ss << getIndentation(indent) << "]";
        }
        else { ss << data; }
        return ss.str();
    }

    std::string print(Data const& data) {
        return prettyPrint(data, 1, 0);
    }

}  // namespace JSON
