#ifndef OPERATOR_H
#define OPERATOR_H
#include "Matrix.h"
#include "Token.h"

class Operator : public Token {
public:
    Operator();
};

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