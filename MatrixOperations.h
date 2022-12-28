#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <vector>
#include <memory>
#include <cmath>

#include "Matrix.h"
#include "Bool.h"
#include "Float.h"

#include "Exception.h"


namespace MatrixOperations {
    std::shared_ptr<Operand> matrixAddition(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixInverse(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixEqual(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixDeterminant(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixTranspose(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> Select(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Matrix> removeRowAndColumn(const std::shared_ptr<Matrix>& matrix, int removeRow, int removeCol);
    std::shared_ptr<Operand> matrixFloatDivision(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixFloatAddition(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixFloatSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> matrixFloatMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatMatrixMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    
    void flipMatrixAlongDiagonal(std::shared_ptr<Matrix>& matrix);
    bool equalMatrix(const std::shared_ptr<Operand>& matrix1, const std::shared_ptr<Operand>& matrix2);
};

#endif