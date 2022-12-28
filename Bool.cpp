#include "Bool.h"

std::string Bool::getTypeName() const {
    return "bool";
}

bool Bool::getValue() const {
    return _value;
}
void Bool::print() const {
    std::cout << _value << std::endl;
}

Bool::Bool(bool value) {
    _value = value;
}
