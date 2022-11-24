#include "matrixAdd.h"

Matrix* matrixAdd::do_operation(const Matrix& m1, const Matrix& m2) {
    int n = m1.getRowCount();
    int m = m2.getColCount();
    auto m3 = std::make_unique<Matrix>(n, m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            m3->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
    return m3.release();
}