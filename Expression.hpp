#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include <vector>
#include <string>

class OperationRegistry;

class Operand;

class Expression {
public:
    virtual std::shared_ptr<const Operand> evaluate() const = 0;
};

#endif
