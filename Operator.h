#include "Matrix.h"
#include "Token.h"

class Operator : public Token {
public:
    Operator();
    virtual void doStuff() override;
};

class ImatrixOperation : public Operator{
public:
    
};

class IbinMatOperations : public ImatrixOperation {
public:
    virtual double do_operation(Matrix&, Matrix&) = 0;

};

class IternMatOperations : public IbinMatOperations {
public:
    virtual double do_operation(Matrix&, Matrix&, Matrix&) = 0;

};

class matrixAdd : public IbinMatOperations {
public:
    matrixAdd();
    virtual double do_operation(Matrix&, Matrix&) override;
};

class matrixSub : public IbinMatOperations {
public:
    matrixSub();
    virtual double do_operation(Matrix&, Matrix&) override;
};

class matrixDiv : public IbinMatOperations {
public:
    matrixDiv();
    virtual double do_operation(Matrix&, Matrix&) override;
};

class matrixMul : public IbinMatOperations {
public:
    matrixMul();
    virtual double do_operation(Matrix&, Matrix&) override;
};