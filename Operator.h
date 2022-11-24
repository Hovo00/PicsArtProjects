#ifndef OPERATOR_H
#define OPERATOR_H
#include "Matrix.h"
#include "Token.h"

class Operator : public Node {
public:
    Operator();
    virtual std::shared_ptr<Operand> evaluate() override;
    std::vector<std::shared_ptr<Node> > childs;
};

return left.evaluate();

class ImatrixOperation : public Operator{
public:
    
};

class IbinMatOperations : public ImatrixOperation {
public:
    virtual int tokenData() override;
    virtual Matrix* doStuff(std::vector<Operand*>) override;
    virtual Matrix* do_operation(const Matrix&, const Matrix&) = 0;
};

class IternMatOperations : public ImatrixOperation {
public:
    virtual int tokenData() override;
    virtual Matrix* doStuff(std::vector<Operand*>) override;
    virtual Matrix* do_operation(const Matrix&, const Matrix&, const Matrix&) = 0;
};

#endif