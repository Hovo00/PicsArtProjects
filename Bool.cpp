#include "Bool.hpp"
#include <string>

std::string Bool::getTypeName() const {
    return "bool";
}

bool Bool::getValue() const {
    return _value;
}

std::string Bool::toString() const {
    return std::to_string(_value);
}

Bool::Bool(bool value) {
    _value = value;
}
