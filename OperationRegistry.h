#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include <cmath>
#include "Matrix.h"
#include "Float.h"
#include "Exception.h"

namespace OperationRegistry {
    std::shared_ptr<Operand> matrixAddition(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatAddition(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixSubtract(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatSubtract(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixMult(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatMult(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixInverse(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixDeterminant(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixTranspose(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> Select(std::vector<std::shared_ptr<Operand> > arguments);
    bool equalMatrix(const std::shared_ptr<Operand>& matrix1, const std::shared_ptr<Operand>& matrix2);
    std::shared_ptr<Operand> sinus(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> cosinus(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Matrix> removeRowAndColumn(const std::shared_ptr<Matrix>& matrix, int removeRow, int removeCol);
    void flipMatrixAlongDiagonal(std::shared_ptr<Matrix>& matrix);
    using FUNCTION = std::function<std::shared_ptr<Operand>(std::vector<std::shared_ptr<Operand> >)>;

    extern std::unordered_map<std::string, FUNCTION> operMap;
    extern void initializeOperationMap();
};

#endif