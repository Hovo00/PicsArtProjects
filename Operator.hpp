#ifndef OPERATOR_H
#define OPERATOR_H

#include "Expression.hpp"
#include "OperationRegistry.hpp"
#include "Exception.hpp"

class Operator : public Expression {
public:
    Operator(std::string operatorName, const std::vector<std::shared_ptr<Expression> >& arguments);
public:
    std::shared_ptr<const Operand> evaluate(const OperationRegistry& registry) const override;
private:
    std::shared_ptr<const Operand> doOperation(const std::vector<std::shared_ptr<const Operand> >& operands,
                                               const OperationRegistry& registry) const;
private:
    std::vector<std::shared_ptr<Expression> > _arguments;
    std::string _operatorName;
};

#endif
