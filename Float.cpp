#include "Float.h"


Float::Float(std::string numb) {
    std::string temp;
    for (int i = 1; i < numb.size(); ++i) {
        temp.push_back(numb[i]);
    }
    value = std::stof(temp);
    std::cout << "i been here " << value << std::endl;
}

void Float::printValue() {
    std::cout << value;
}
Float::Float(float numb) {
    value = numb;
}
float Float::getValue() {
    return value;
}