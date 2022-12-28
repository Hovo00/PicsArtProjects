#include "Float.h"

std::string Float::getTypeName() const {
    return "float";
}

void Float::print() const{
    std::cout << _value;
}

Float::Float(float number){
    _value = number;
}

float Float::getValue() const{
    return _value;
}