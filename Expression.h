#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include <vector>
#include <string>

class Operand;

class Expression {
public:
    virtual std::shared_ptr<Operand> evaluate() = 0;
};

#endif
