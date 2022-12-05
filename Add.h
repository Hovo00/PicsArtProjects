#ifndef ADDITION_H
#define ADDITION_H
#include <typeinfo>
#include <exception>
#include <variant>

#include "Operator.h"
#include "Matrix.h"
#include "Float.h"


class Add : public IbinOperations {
public:
    Add() = default;
    Add(std::vector<std::shared_ptr<Expression> >& children);
    std::shared_ptr<Operand> doOperation(std::vector<std::shared_ptr<Operand> >) override;
    std::string getTypename() override;
private:
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix> matrix1, std::shared_ptr<Matrix> matrix2);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix> matrix, std::shared_ptr<Float> flt);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float> float1, std::shared_ptr<Float> float2);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float> flt, std::shared_ptr<Matrix> matrix);
};

#endif
