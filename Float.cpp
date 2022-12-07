#include "Float.h"


Float::Float(std::string numb) {
    std::string temp;
    for (int i = 1; i < numb.size(); ++i) {
        temp.push_back(numb[i]);
    }
    value = std::stof(temp);
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