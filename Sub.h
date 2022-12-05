#ifndef SUBTRACT_H
#define SUBTRACT_H
#include <typeinfo>
#include <exception>
#include "Matrix.h"
#include "Float.h"

#include "Operator.h"

class Expression;

class Sub : public IbinOperations {
public:
    Sub() = default;
    Sub(std::vector<std::shared_ptr<Expression> >& children);
    std::shared_ptr<Operand> doOperation(std::vector<std::shared_ptr<Operand> > operands) override;
    std::string getTypename() override;
private:
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix> matrix1, std::shared_ptr<Matrix> matrix2);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Matrix> matrix, std::shared_ptr<Float> flt);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float> float1, std::shared_ptr<Float> float2);
    std::shared_ptr<Operand> doOper(std::shared_ptr<Float> flt, std::shared_ptr<Matrix> matrix);
};

#endif
