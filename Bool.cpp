#include "Bool.hpp"

bool Bool::getValue() const {
    return _value;
}

std::string Bool::toString() const {
    return std::to_string(_value);
}

Bool::Bool(bool value) {
    _value = value;
}
