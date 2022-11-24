#include "matrixMul.h"
Matrix* matrixMul::do_operation(const Matrix& m1, const Matrix& m2) {
    int n = m1.getRowCount();
    int c = m1.getColCount();
    int m = m2.getColCount();
    //std::cout << std::endl << "cheeeck"<< n << " " << c << " " << m << " " << std::endl;
    //Matrix m3(n, m);
    auto m3 = std::make_unique<Matrix>(n, m);
    for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < m; ++j) {
		    for (int k = 0; k < c; ++k) {
			    m3->matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
		    }
	    }
    }
    return m3.release();
}