#ifndef MATRIX_H
#define MATRIX_H

#include <stack>
#include <iostream>
#include "TypeInfo.h"
#include "Expression.h"
#include "Operand.h"


class Matrix : public Operand {
public:
    Matrix(int row, int col);
    Matrix(const std::string& matrixString);
public:
    int getColCount() const;
    int getRowCount() const;
    bool initMatrix(const std::string& matrixString);
public:
    void printValue() const override;
    std::string getTypename() const override;
private:
    int rowCount;
    int colCount;
public:
    std::vector<std::vector<double>> matrix;
};

#endif
