#ifndef FLOAT_H
#define FLOAT_H
#include <iostream>
#include "Operand.h"

class Float : public Operand {
public:
    Float(std::string numb);
    Float(float numb);
public:
    void printValue() const override;
    std::string getTypename() const override;
public:
    float getValue() const;
private:
    float _value;
};

#endif