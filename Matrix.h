#ifndef MATRIX_H
#define MATRIX_H

#include <stack>
#include <iostream>
//#include "TypeInfo.h"
#include "Expression.h"
#include "Operand.h"


class Matrix : public Operand {
public:
    Matrix(int row, int col);
    Matrix(const std::vector<std::vector<float> >& matrix);
public:
    int getColCount() const;
    int getRowCount() const;
    float& at(int row, int col);
public:
    void print() const override;
    std::string getTypeName() const override;
private:
    int _rowCount;
    int _colCount;
    std::vector<std::vector<float> > _matrix;
};

#endif
