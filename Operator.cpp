#include "Operator.h"

Operator::Operator() {
    tokType = TokenType::Operator;
}
Matrix IbinMatOperations::doStuff(std::vector<Matrix> vec) {
    return do_operation(vec[0], vec[1]);
}
Matrix IternMatOperations::doStuff(std::vector<Matrix> vec) {
    return do_operation(vec[0], vec[1], vec[2]);
}

Matrix matrixMul::do_operation(const Matrix& m1, const Matrix& m2) {
    int n = m1.getRowCount();
    int c = m1.getColCount();
    int m = m2.getColCount();
    std::cout << n << " " << c << " " << m << " " << std::endl;
    Matrix m3(n, m);
    for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < n; ++j) {
		    for (int k = 0; k < m; ++k) {
			    m3.matrix[i][k] += m1.matrix[i][j] * m2.matrix[j][k];
		    }
	    }
    }
    return m3;
}
Matrix matrixSub::do_operation(const Matrix& m1, const Matrix& m2) {
    int n = m1.getRowCount();
    int m = m2.getColCount();
    Matrix m3(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m3.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
        }
    }
    return m3;
}
Matrix matrixAdd::do_operation(const Matrix& m1, const Matrix& m2) {
    int n = m1.getRowCount();
    int m = m2.getColCount();
    Matrix m3(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m3.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
    return m3;
}

matrixMul::matrixMul() {
    prec = 2;
}
matrixSub::matrixSub() {
    prec = 1;
}
matrixAdd::matrixAdd() {
    prec = 1;
}