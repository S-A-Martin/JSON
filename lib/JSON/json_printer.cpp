#include "json_printer.h"

int JSON::indentation = 0;

std::string JSON::getInd(int indent) {
    std::string spaces;
    for (int i = 0; i < JSON::indentation * indent; i++) {
        spaces += " ";
    }
    return spaces;
}

std::string JSON::prettyPrint(JSON::Data& data, int indent) {
    std::stringstream ss;

    if (data.index() == JSON_OBJECT) {  // i.e JSON::Object a.k.a map
        ss << "{\n";
        JSON::indentation++;
        // iterate and print map
        JSON::Object::iterator it;
        JSON::Object object = std::get<JSON::Object>(data.value);
        for (it = object.begin(); it != object.end(); it++) {
            ss << getInd(indent) << "\"" << it->first << "\": " << prettyPrint(it->second, indent);
            if (it != std::prev(object.end(), 1)) { ss << ","; }
            ss << "\n";
        }
        JSON::indentation--;
        ss << getInd(indent) << "}";
    }

    else if (data.index() == JSON_ARRAY) { ss << prettyPrint(std::get<JSON::Array>(data.value), indent); }
    else { ss << data; }
    return ss.str();
}

std::string JSON::prettyPrint(JSON::Array& array, int indent) {
    std::stringstream ss;
    ss << "[\n";
    JSON::indentation++;
    for (int i = 0; i < array.size(); i++) {
        ss << getInd(indent) << prettyPrint(array[i], indent);
        if (i != array.size() - 1) { ss << ","; }
        ss << "\n";
    }
    JSON::indentation--;
    ss << getInd(indent) << "]";
    return ss.str();
}
