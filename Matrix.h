#ifndef MATRIX_H
#define MATRIX_H

#include <stack>
#include <iostream>
#include "TypeInfo.h"
#include "Expression.h"
#include "Operand.h"


class Matrix : public Operand {
public:
    Matrix();
    Matrix(int row, int col);
    Matrix(const std::string& str);
public:
    int getColCount() const;
    int getRowCount() const;
    void printMat();
    bool initMatrix(const std::string& str);
public:
    void printValue() override;
private:
    int rowCount;
    int colCount;
public:
    std::vector<std::vector<double>> matrix;
};

#endif
