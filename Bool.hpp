#ifndef BOOL_H
#define BOOL_H

#include <iostream>
#include <string>

#include "Operand.hpp"


class Bool : public Operand {
public:
    Bool(bool value);
    std::string getTypeName() const override;
    std::string toString() const override;
public:
    bool getValue() const;
private:
    bool _value;
};

#endif