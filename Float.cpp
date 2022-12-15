#include "Float.h"


Float::Float(std::string number) {
    _value = std::stof(number);
}
std::string Float::getTypename() const {
    return "float";
}

void Float::printValue() const{
    std::cout << _value;
}
Float::Float(float number) {
    _value = number;
}
float Float::getValue() const{
    return _value;
}