#include "OperationRegistry.h"

void OperationRegistry::initializeOperationMap();
std::unordered_map<std::string, OperationRegistry::FUNCTION> OperationRegistry::operMap;

std::shared_ptr<Operand> OperationRegistry::matrixAddition(std::vector<std::shared_ptr<Operand> > arguments) {
    auto m1 = std::static_pointer_cast<Matrix>(arguments[0]);
    auto m2 = std::static_pointer_cast<Matrix>(arguments[1]);
    assert(m1->getColCount() == m2->getColCount() && m1->getRowCount() == m2->getRowCount());

    int n = m1->getRowCount();
    int m = m2->getColCount();
    auto m3 = std::make_shared<Matrix>(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m3->at(i, j) = m1->at(i, j) + m2->at(i, j);
        }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatAddition(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() + f2->getValue());
}
std::shared_ptr<Operand> OperationRegistry::matrixSubtraction(std::vector<std::shared_ptr<Operand> > arguments) {
    auto m1 = std::static_pointer_cast<Matrix>(arguments[0]);
    auto m2 = std::static_pointer_cast<Matrix>(arguments[1]);
    assert(m1->getColCount() == m2->getColCount() && m1->getRowCount() == m2->getRowCount());
    int n = m1->getRowCount();
    int m = m2->getColCount();
    auto m3 = std::make_shared<Matrix>(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m1->at(i, j) = m1->at(i, j) - m2->at(i, j);
        }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatSubtraction(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() - f2->getValue());
}
std::shared_ptr<Operand> OperationRegistry::matrixMultiplication(std::vector<std::shared_ptr<Operand> > arguments) {
    auto m1 = std::static_pointer_cast<Matrix>(arguments[0]);
    auto m2 = std::static_pointer_cast<Matrix>(arguments[1]);
    assert(m1->getColCount() == m2->getRowCount());
    int n = m1->getRowCount();
    int c = m1->getColCount();
    int m = m2->getColCount();
    auto m3 = std::make_shared<Matrix>(n, m);
    for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < m; ++j) {
		    for (int k = 0; k < c; ++k) {
			    m3->at(i, j) += m1->at(i, k) * m2->at(k, j);
		    }
	    }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatMultiplication(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() * f2->getValue());
}
std::shared_ptr<Operand> OperationRegistry::floatDivision(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() / f2->getValue());
}

std::shared_ptr<Operand> OperationRegistry::matrixDeterminant(std::vector<std::shared_ptr<Operand> > arguments) {
    auto matrix = std::static_pointer_cast<Matrix>(arguments[0]);
    float det = 0;
    int n = matrix->getRowCount();
    auto subMatrix = std::make_shared<Matrix>(n - 1, n - 1);
    if (n == 2) {
        det = (matrix->at(0, 0) * matrix->at(1, 1)) - (matrix->at(1, 0) * matrix->at(0, 1));
    }
    else {
        for (int x = 0; x < n; ++x) {
            int subi = 0;
            for (int i = 1; i < n; ++i) {
                int subj = 0;
                for (int j = 0; j < n; ++j) {
                    if (j == x) {
                        continue;
                    }
                    subMatrix->at(subi, subj) = matrix->at(i, j);
                    subj++;
                }
                subi++;
            }
        auto subDet = std::static_pointer_cast<Float>(matrixDeterminant(std::vector<std::shared_ptr<Operand> >{subMatrix}));
        det = det + (pow(-1, x) * matrix->at(0, x) * subDet->getValue());
        }
   }
   return std::make_shared<Float>(det);
}

std::shared_ptr<Matrix> OperationRegistry::removeRowAndColumn(const std::shared_ptr<Matrix>& matrix, int removeRow, int removeCol) {
    int size = matrix->getRowCount();
    int i = 0;
    int j = 0;
    int subI = 0;
    int subJ = 0;
    auto subMatrix = std::make_shared<Matrix>(size - 1, size - 1);
    //Matrix subMatrix(size - 1, size - 1);
    while (i < size) {
        if (i == removeRow) {
            ++i;
            continue;
        }
        subJ = 0;
        j = 0;
        while (j < size) {
            if (j == removeCol) {
                ++j;
                continue;
            }
            subMatrix->at(subI, subJ) = matrix->at(i, j);
            //std::cout << subMatrix->at(subI, subJ) << std::endl;
            ++subJ;
            ++j;
        }
        ++i;
        ++subI;
    }
    return subMatrix;
}

void OperationRegistry::flipMatrixAlongDiagonal(std::shared_ptr<Matrix>& matrix) {
    int size = matrix->getColCount();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::swap(matrix->at(i, j), matrix->at(j, i));
        }
    }
}

std::shared_ptr<Operand> OperationRegistry::matrixInverse(std::vector<std::shared_ptr<Operand> > arguments) {
    auto matrix = std::static_pointer_cast<Matrix>(arguments[0]);
    int size =  matrix->getRowCount();
    auto inverseMatrix = std::make_shared<Matrix>(size, size);
    auto determinant = std::static_pointer_cast<Float>(matrixDeterminant(std::vector<std::shared_ptr<Operand> >{matrix}));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            auto subMatrix = OperationRegistry::removeRowAndColumn(matrix, i, j);
            auto coFactor = std::static_pointer_cast<Float>(matrixDeterminant(std::vector<std::shared_ptr<Operand> >{subMatrix}));
            inverseMatrix->at(i, j) = pow(-1, i + j) * coFactor->getValue() / determinant->getValue();
        }
    }
    flipMatrixAlongDiagonal(inverseMatrix);
    return inverseMatrix;
}

std::shared_ptr<Operand> OperationRegistry::matrixTranspose(std::vector<std::shared_ptr<Operand> > arguments) {
    auto matrix = std::static_pointer_cast<Matrix>(arguments[0]);
    auto transposedMatrix = std::make_shared<Matrix>(matrix->getColCount(), matrix->getRowCount());
    for (int i = 0; i < matrix->getRowCount(); ++i) {
        for (int j = 0; j < matrix->getColCount(); ++j) {
            transposedMatrix->at(j, i) = matrix->at(i, j);
        }
    }
    return transposedMatrix;
}
std::shared_ptr<Operand> OperationRegistry::sinus(std::vector<std::shared_ptr<Operand> > arguments) {
    auto varFloat = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Float>(std::sin(varFloat->getValue() * 3.14159 / 180));
}
std::shared_ptr<Operand> OperationRegistry::cosinus(std::vector<std::shared_ptr<Operand> > arguments) {
    auto varFloat = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Float>(std::cos(varFloat->getValue() * 3.14159 / 180));
}

bool OperationRegistry::equalMatrix(const std::shared_ptr<Operand>& m1, const std::shared_ptr<Operand>& m2) {
    auto matrix1 = std::static_pointer_cast<Matrix>(m1);
    auto matrix2 = std::static_pointer_cast<Matrix>(m2);
    if (matrix1->getColCount() != matrix2->getColCount() || matrix1->getRowCount() != matrix2->getRowCount()) {
        return false;
    }
    for (int i = 0; i < matrix1->getRowCount(); ++i) {
        for (int j = 0; j < matrix1->getRowCount(); ++j) {
            if (matrix1->at(i, j) != matrix2->at(i, j)) {
                return false;
            }
        }
    }
    return true;
}


std::shared_ptr<Operand> OperationRegistry::Select(std::vector<std::shared_ptr<Operand> > arguments) {
    if (arguments[0]->getTypename() != "matrix" || arguments[1]->getTypename() != "matrix" || arguments[2]->getTypename() != "matrix") {
        throw UnsupportedOperatorArguments("select not supported for this types");
    }
    auto matrix1 = std::static_pointer_cast<Matrix>(arguments[0]);
    std::vector<std::shared_ptr<Operand> > args;
    args.push_back(arguments[1]);
    args.push_back(arguments[2]);
    auto result = operMap["*matrixmatrix"](args);
    // if (equalMatrix(matrix1, result)) {
    //     return matrix1;
    // }
    return equalMatrix(matrix1, result) ? matrix1 : result;
}

void OperationRegistry::initializeOperationMap() {
    OperationRegistry::operMap["+matrixmatrix"] = OperationRegistry::matrixAddition;
    OperationRegistry::operMap["-matrixmatrix"] = OperationRegistry::matrixSubtraction;
    OperationRegistry::operMap["*matrixmatrix"] = OperationRegistry::matrixMultiplication;
    OperationRegistry::operMap["+floatfloat"] = OperationRegistry::floatAddition;
    OperationRegistry::operMap["-floatfloat"] = OperationRegistry::floatSubtraction;
    OperationRegistry::operMap["*floatfloat"] = OperationRegistry::floatMultiplication;
    OperationRegistry::operMap["inversematrix"] = OperationRegistry::matrixInverse;
    OperationRegistry::operMap["detmatrix"] = OperationRegistry::matrixDeterminant;
    OperationRegistry::operMap["transposematrix"] = OperationRegistry::matrixTranspose;
    OperationRegistry::operMap["sinfloat"] = OperationRegistry::sinus;
    OperationRegistry::operMap["cosfloat"] = OperationRegistry::cosinus;
    OperationRegistry::operMap["selectmatrixmatrixmatrix"] = OperationRegistry::Select;
    OperationRegistry::operMap["/floatfloat"] = OperationRegistry::floatDivision;
}
