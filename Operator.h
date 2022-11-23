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
    virtual Matrix* doStuff(std::vector<Matrix>) override;
    virtual Matrix* do_operation(const Matrix&, const Matrix&) = 0;
};

class IternMatOperations : public ImatrixOperation {
public:
    virtual int tokenData() override;
    virtual Matrix* doStuff(std::vector<Matrix>) override;
    virtual Matrix* do_operation(const Matrix&, const Matrix&, const Matrix&) = 0;
};

class matrixAdd : public IbinMatOperations {
public:
    matrixAdd();
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};

class matrixSub : public IbinMatOperations {
public:
    matrixSub();
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};

class matrixMul : public IbinMatOperations {
public:
    matrixMul();
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};