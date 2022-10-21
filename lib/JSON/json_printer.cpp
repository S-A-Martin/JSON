#include "json_printer.h"

static int indentWidth = 0;

// Stream JSON::Data::operator Overload
std::ostream& JSON::operator<<(std::ostream& os, JSON::Data const& d) {
    switch (d.index()) {
    case JSON::Type::JSON_NULL:
        os << "null";
        break;
    case JSON::Type::INT:
        os << std::get<int>(d.value);
        break;
    case JSON::Type::UINT:
        os << std::get<unsigned int>(d.value);
        break;
    case JSON::Type::DOUBLE:
        os << std::get<double>(d.value);
        break;
    case JSON::Type::BOOL:
        os << (std::get<bool>(d.value) ? "true" : "false");
        break;
    case JSON::Type::STD_STRING:
        os << "\"" << std::get<std::string>(d.value) << "\"";
        break;
    case JSON::Type::JSON_OBJECT:
        os << "\"Invalid Output (JSON::Object)\"";
        break;
    case JSON::Type::JSON_ARRAY:
        os << "\"Invalid Output (JSON::Array)\"";
        break;
    }

    return os;
}

std::string JSON::getInd(int indent) {
    std::string spaces;
    for (int i = 0; i < indentWidth * indent; ++i) {
        spaces += " ";
    }
    return spaces;
}

std::string JSON::prettyPrint(JSON::Data const& data, int indent) {
    std::stringstream ss;

    if (data.index() == JSON_OBJECT) {
        ss << "{\n";
        indentWidth++;

        JSON::Object::const_iterator it;
        JSON::Object const object = std::get<JSON::Object>(data.value);
        for (it = object.begin(); it != object.end(); ++it) {
            ss << getInd(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
            if (it != std::prev(object.end(), 1)) { ss << ","; }
            ss << "\n";
        }
        indentWidth--;
        ss << getInd(indent) << "}";
    }

    else if (data.index() == JSON_ARRAY) { ss << prettyPrint(std::get<JSON::Array>(data.value), indent); }
    else { ss << data; }
    return ss.str();
}

std::string JSON::prettyPrint(JSON::Array const& array, int indent) {
    std::stringstream ss;
    ss << "[\n";
    ++indentWidth;
    for (int i = 0; i < array.size(); ++i) {
        ss << getInd(indent) << prettyPrint(array[i], indent);
        if (i != array.size() - 1) { ss << ","; }
        ss << "\n";
    }
    indentWidth--;
    ss << getInd(indent) << "]";
    return ss.str();
}
