#ifndef FLOAT_H
#define FLOAT_H
#include <iostream>
#include "Operand.h"

class Float : public Operand {
public:
    Float(float numb);
public:
    void print() const override;
    std::string getTypeName() const override;
public:
    float getValue() const;
private:
    float _value;
};

#endif