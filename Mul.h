#ifndef MULTIPLE_H
#define MULTIPLE_H
#include <typeinfo>
#include <exception>
#include "Matrix.h"

#include "Operator.h"

class Mul : public IbinOperations {
public:
    Mul() = default;
    Mul(std::vector<std::shared_ptr<Expression> >&);
    std::shared_ptr<Operand> doOperation(std::vector<std::shared_ptr<Operand> >) override;
    std::string getInfo() override;
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix>, std::shared_ptr<Matrix>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix>, std::shared_ptr<Float>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float>, std::shared_ptr<Float>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float>, std::shared_ptr<Matrix>);
};

#endif