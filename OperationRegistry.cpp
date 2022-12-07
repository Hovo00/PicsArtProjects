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
            m3->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
        }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatAddition(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() + f2->getValue());
}
std::shared_ptr<Operand> OperationRegistry::matrixSubtract(std::vector<std::shared_ptr<Operand> > arguments) {
    auto m1 = std::static_pointer_cast<Matrix>(arguments[0]);
    auto m2 = std::static_pointer_cast<Matrix>(arguments[1]);
    assert(m1->getColCount() == m2->getColCount() && m1->getRowCount() == m2->getRowCount());
    int n = m1->getRowCount();
    int m = m2->getColCount();
    auto m3 = std::make_shared<Matrix>(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m3->matrix[i][j] = m1->matrix[i][j] - m2->matrix[i][j];
        }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatSubtract(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() - f2->getValue());
}
std::shared_ptr<Operand> OperationRegistry::matrixMult(std::vector<std::shared_ptr<Operand> > arguments) {
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
			    m3->matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
		    }
	    }
    }
    return m3;
}
std::shared_ptr<Operand> OperationRegistry::floatMult(std::vector<std::shared_ptr<Operand> > arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() * f2->getValue());
}

void OperationRegistry::initializeOperationMap() {
    OperationRegistry::operMap["+matrixmatrix"] = OperationRegistry::matrixAddition;
    OperationRegistry::operMap["-matrixmatrix"] = OperationRegistry::matrixSubtract;
    OperationRegistry::operMap["*matrixmatrix"] = OperationRegistry::matrixMult;
    OperationRegistry::operMap["+floatfloat"] = OperationRegistry::floatAddition;
    OperationRegistry::operMap["-floatfloat"] = OperationRegistry::floatSubtract;
    OperationRegistry::operMap["*floatfloat"] = OperationRegistry::floatMult;

}