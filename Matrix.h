#ifndef MATRIX_H
#define MATRIX_H

#include <stack>
#include <iostream>
#include "TypeInfo.h"
#include "Expression.h"

class Operand : public Expression ,
                public std::enable_shared_from_this<Operand>{
public:
    std::shared_ptr<Operand> evaluate() override;
    virtual void printValue() = 0;
};

class Float : public Operand {
public:
    std::string getInfo() override;
    void printValue() override;
    // float getValue() {
    //     return value;
    // }
private:
    float value;
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
    std::string getInfo() override;  
    void printValue() override;

private:
    int rowCount;
    int colCount;
public:
    std::vector<std::vector<double>> matrix;
};

#endif
