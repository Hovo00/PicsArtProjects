#ifndef ADDITION_H
#define ADDITION_H
#include <typeinfo>
#include <exception>
#include <variant>

#include "Operator.h"
#include "Matrix.h"


class Add : public IbinOperations {
public:
    Add() = default;
    Add(std::vector<std::shared_ptr<Expression> >&);
    std::shared_ptr<Operand> doOperation(std::vector<std::shared_ptr<Operand> >) override;
    std::string getInfo() override;
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix>, std::shared_ptr<Matrix>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix>, std::shared_ptr<Float>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float>, std::shared_ptr<Float>);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float>, std::shared_ptr<Matrix>);
};

#endif
