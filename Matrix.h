#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <stack>
#include "TypeInfo.h"
#include "Token.h"

class Operand : public Token{
public:
    virtual void printOperand() = 0;
};

class Matrix : public Operand {
public:
    Matrix();
    Matrix(int row, int col);
    Matrix(const std::string&);
public:
    int getColCount() const;
    int getRowCount() const;
    void printMat();
    bool initMatrix(const std::string&);
public:
    virtual Matrix* doStuff(std::vector<Operand*>) override;
    virtual void printOperand() override;
    virtual int tokenData() override;
  
private:
    int rowCount;
    int colCount;
public:
    std::vector<std::vector<double>> matrix;
};

#endif