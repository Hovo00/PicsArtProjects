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
    std::string getTypename() const override;
private:
    std::vector<std::shared_ptr<Expression> > arguments;
    std::string operatorType;
private:
    std::shared_ptr<Operand> doOperation(const std::vector<std::shared_ptr<Operand> >& operands) const;
    void throwInvalidArgumentsError(const std::vector<std::shared_ptr<Operand> >& arguments) const;
};



#endif
