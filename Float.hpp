#ifndef FLOAT_H
#define FLOAT_H
#include <sstream>
#include "Operand.hpp"

class Float : public Operand {
public:
    Float(double number);
public:
    std::string toString() const override;
    std::string getTypeName() const override;
public:
    double getValue() const;
private:
    double _value;
};

#endif