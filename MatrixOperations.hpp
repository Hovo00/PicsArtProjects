#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <vector>
#include <memory>
#include <cmath>

#include "Matrix.hpp"
#include "Bool.hpp"
#include "Float.hpp"

#include "Exception.hpp"


namespace MatrixOperations {
    std::shared_ptr<const Operand> matrixAddition(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixSubtraction(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixInverse(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixEqual(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixDeterminant(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixTranspose(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> Select(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Matrix> removeRowAndColumn(const std::shared_ptr<const Matrix>& matrix, int removeRow, int removeCol);
    std::shared_ptr<const Operand> matrixFloatDivision(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixFloatAddition(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixFloatSubtraction(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> matrixFloatMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleMatrixMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments);
    void flipMatrixAlongDiagonal(std::shared_ptr<Matrix>& matrix);
    bool equalMatrix(const std::shared_ptr<const Operand>& matrix1, const std::shared_ptr<const Operand>& matrix2);
};

#endif