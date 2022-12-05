#ifndef OPERATOR_H
#define OPERATOR_H
#include "Matrix.h"
#include "Expression.h"

class Operator : public Expression {
public:
    std::shared_ptr<Operand> evaluate() override;
public:
    virtual std::string getTypename() = 0;
    virtual std::shared_ptr<Operand> doOperation(std::vector<std::shared_ptr<Operand> > operands) = 0;
    virtual int operandCount() = 0;
protected:
    std::vector<std::shared_ptr<Expression> > children;
};

class IbinOperations : public Operator {
public:
    int operandCount() override;
};

class IternOperations : public Operator {
public:
    int operandCount() override;
};

#endif
