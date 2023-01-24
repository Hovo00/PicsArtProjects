#ifndef MATRIX_H
#define MATRIX_H

#include <stack>
#include <iostream>
#include <sstream>
#include "Expression.hpp"
#include "Operand.hpp"


class Matrix : public Operand {
public:
    Matrix(int row, int col);
    Matrix(const std::vector<std::vector<double> >& matrix);
public:
    int getColCount() const;
    int getRowCount() const;
    const double& at(int row, int col) const;
    double& at(int row, int col);

public:
    std::string toString() const override;
    std::string getTypeName() const override;
private:
    int _rowCount;
    int _colCount;
    std::vector<std::vector<double> > _matrix;
};

#endif
