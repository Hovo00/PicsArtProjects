#ifndef FUNCTIONS_H_SS
#define FUNCTIONS_H_SS

#include <iostream>
#include <cmath>

#include "Matrix.h"
#include "Float.h"
#include "Exception.h"


namespace Functions {
    std::shared_ptr<Operand> matrixAddition(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatAddition(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatDivision(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixFloatDivision(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixInverse(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixDeterminant(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixTranspose(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> Select(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> sinus(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> cosinus(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Matrix> removeRowAndColumn(const std::shared_ptr<Matrix>& matrix, int removeRow, int removeCol);

    bool equalMatrix(const std::shared_ptr<Operand>& matrix1, const std::shared_ptr<Operand>& matrix2);
    void flipMatrixAlongDiagonal(std::shared_ptr<Matrix>& matrix);
};

#endif