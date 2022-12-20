#ifndef OPERATOR_H
#define OPERATOR_H
#include "Matrix.h"
#include "Expression.h"
#include "OperationRegistry.h"
#include "Exception.h"

class Operator : public Expression {
public:
    Operator(std::string operatorType, const std::vector<std::shared_ptr<Expression> >& arguments);
public:
    std::shared_ptr<Operand> evaluate() override;
    std::string getTypeName() const override;
private:
    std::shared_ptr<Operand> doOperation(const std::vector<std::shared_ptr<Operand> >& operands) const;
    void throwInvalidArgumentsError(const std::vector<std::shared_ptr<Operand> >& arguments) const;
private:
    std::vector<std::shared_ptr<Expression> > _arguments;
    std::string _operatorType;
};

#endif
