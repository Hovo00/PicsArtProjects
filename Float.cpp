#include "Float.hpp"
#include <string>

std::string Float::toString() const {
    //string stream for removing trailing zeroes
    std::stringstream number;
    number << _value;
    return number.str();
}

Float::Float(double number){
    _value = number;
}

double Float::getValue() const{
    return _value;
}
