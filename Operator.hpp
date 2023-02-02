#ifndef OPERATOR_H
#define OPERATOR_H

#include "Expression.hpp"
#include "OperationRegistry.hpp"
#include "Exception.hpp"


class Operator : public Expression {
    using OperationHandler = std::function<std::shared_ptr<const Operand>(std::vector<std::shared_ptr<const Operand> >)>;
public:
    Operator(std::string operatorName, const std::vector<std::shared_ptr<Expression> >& arguments, OperationHandler handler);
public:
    std::shared_ptr<const Operand> evaluate() const override;
private:
    std::string _operatorName;
    std::vector<std::shared_ptr<Expression> > _arguments;
    OperationHandler _handler;
};

#endif
