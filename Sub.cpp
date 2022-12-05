#include "Sub.h"

Sub::Sub(std::vector<std::shared_ptr<Expression> >& chlds) {
    children = chlds;
}

std::shared_ptr<Operand> Sub::doOperation(std::vector<std::shared_ptr<Operand> > args) {
    if (auto m1 = std::dynamic_pointer_cast<Float>(args[0])) {
        if (auto m2 = std::dynamic_pointer_cast<Float>(args[1])) {
            return doOper(m1, m2);
        }
        else if (auto m2 = std::dynamic_pointer_cast<Matrix>(args[1])) {
            return doOper(m1, m2);
        }
        //throw exception
        }
    else if (auto m1 = std::dynamic_pointer_cast<Matrix>(args[0])) {
        if (auto m2 = std::dynamic_pointer_cast<Float>(args[1])) {
            return doOper(m1, m2);
        }
        else if (auto m2 = std::dynamic_pointer_cast<Matrix>(args[1])) {
            return doOper(m1, m2);
        }
        //throw exception
        }
    return std::make_shared<Matrix>();
}
std::shared_ptr<Operand> Sub::doOper(std::shared_ptr<Matrix> m1, std::shared_ptr<Matrix> m2) {
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
std::shared_ptr<Operand> Sub::doOper(std::shared_ptr<Matrix> matrix, std::shared_ptr<Float> flt) {
    return std::make_shared<Matrix>();
}
std::shared_ptr<Operand> Sub::doOper(std::shared_ptr<Float> flt1, std::shared_ptr<Float> flt2) {
    return std::make_shared<Float>(flt1->getValue() - flt2->getValue());
}
std::shared_ptr<Operand> Sub::doOper(std::shared_ptr<Float> flt, std::shared_ptr<Matrix> matrix) {
    return std::make_shared<Matrix>();

}
std::string Sub::getTypename() {
    return "-";
}
