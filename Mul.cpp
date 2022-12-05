#include "Mul.h"

Mul::Mul(std::vector<std::shared_ptr<Expression> >& chlds) {
    children = chlds;
}

std::shared_ptr<Operand> Mul::doOperation(std::vector<std::shared_ptr<Operand> > args) {
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
std::shared_ptr<Operand> Mul::doOper(std::shared_ptr<Matrix> m1, std::shared_ptr<Matrix> m2) {
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
std::shared_ptr<Operand> Mul::doOper(std::shared_ptr<Matrix> matrix, std::shared_ptr<Float> flt) {
    return std::make_shared<Matrix>();
}
std::shared_ptr<Operand> Mul::doOper(std::shared_ptr<Float> f1, std::shared_ptr<Float> f2) {
    std::cout << "I do it" << std::endl;
    return std::make_shared<Float>(f1->getValue() * f2->getValue());
}
std::shared_ptr<Operand> Mul::doOper(std::shared_ptr<Float> f1, std::shared_ptr<Matrix> matrix) {
    return std::make_shared<Matrix>();
}
std::string Mul::getTypename() {
    return "*";
}

