#ifndef FLOAT_H
#define FLOAT_H
#include <iostream>
#include "Operand.h"

class Float : public Operand {
public:
    Float(std::string numb);
    Float(float numb);
public:
    void printValue() override;
    float getValue();
private:
    float value;
};

#endif