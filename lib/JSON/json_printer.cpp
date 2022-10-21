#include "json_printer.h"

static int indentWidth = 0;

namespace JSON {

    namespace {  // Annoymous to limit to json_printer.cpp
        std::string getIndentation(int indent) {
            std::string spaces;
            for (int i = 0; i < indentWidth * indent; ++i) {
                spaces += " ";
            }
            return spaces;
        }

        std::string prettyPrint(Array const& array, int indent) {
            std::stringstream ss;
            ss << "[\n";
            ++indentWidth;
            for (int i = 0; i < array.size(); ++i) {
                ss << getIndentation(indent) << prettyPrint(array[i], indent);
                if (i != array.size() - 1) { ss << ","; }
                ss << "\n";
            }
            indentWidth--;
            ss << getIndentation(indent) << "]";
            return ss.str();
        }
    }  // namespace

    // Stream Data::operator Overload
    std::ostream& operator<<(std::ostream& os, Data const& d) {
        switch (d.index()) {
        case Type::JSON_NULL:
            os << "null";
            break;
        case Type::INT:
            os << std::get<int>(d.value);
            break;
        case Type::UINT:
            os << std::get<unsigned int>(d.value);
            break;
        case Type::DOUBLE:
            os << std::get<double>(d.value);
            break;
        case Type::BOOL:
            os << (std::get<bool>(d.value) ? "true" : "false");
            break;
        case Type::STD_STRING:
            os << "\"" << std::get<std::string>(d.value) << "\"";
            break;
        case Type::JSON_OBJECT:
            os << "\"Invalid Output (JSON::Object)\"";
            break;
        case Type::JSON_ARRAY:
            os << "\"Invalid Output (JSON::Array)\"";
            break;
        }

        return os;
    }

    std::string prettyPrint(Data const& data, int indent) {
        std::stringstream ss;

        if (data.index() == JSON_OBJECT) {
            ss << "{\n";
            ++indentWidth;

            Object::const_iterator it;
            Object const object = std::get<Object>(data.value);
            for (it = object.begin(); it != object.end(); ++it) {
                ss << getIndentation(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
                if (it != std::prev(object.end(), 1)) { ss << ","; }
                ss << "\n";
            }
            indentWidth--;
            ss << getIndentation(indent) << "}";
        }

        else if (data.index() == JSON_ARRAY) { ss << prettyPrint(std::get<Array>(data.value), indent); }
        else { ss << data; }
        return ss.str();
    }

}  // namespace JSON
