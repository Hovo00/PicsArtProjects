#include "Float.h"


Float::Float(std::string numb) {
    value = std::stof(numb);
}
std::string Float::getTypename() const {
    return "float";
}

void Float::printValue() const{
    std::cout << value;
}
Float::Float(float numb) {
    value = numb;
}
float Float::getValue() const{
    return value;
}