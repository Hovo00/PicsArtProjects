#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include <vector>
#include <string>

class OperationRegistry;

class Operand;

class Expression {
public:
    virtual std::shared_ptr<const Operand> evaluate(const OperationRegistry&) const = 0;
    virtual std::string getTypeName() const = 0;

    //Expression(const std::string& expressionTypeName)
    //const std::string expressionTypeName;
};

#endif
