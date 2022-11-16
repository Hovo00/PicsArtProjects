#include "Operator.h"

Operator::Operator() {
    tokType = TokenType::Operator;
}
void Operator::doStuff() {

}
double matrixMul::do_operation(Matrix& m1, Matrix& m2) {
    // int n = m1.rowCount;
    // int c = m1.colCount;
    // int m = m2.colCount;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < c; ++j) {
    //         for (int k = 0; k < m; ++k) {
    //             p3[i][k] += p1[i][j] * p2[j][k];
    //         }
    //     }
    // }
    return 4.0;
}
double matrixDiv::do_operation(Matrix&, Matrix&) {
    return 4.0;
}
double matrixSub::do_operation(Matrix&, Matrix&) {
    return 4.0;
}
double matrixAdd::do_operation(Matrix&, Matrix&) {
    return 4.0;
}

matrixMul::matrixMul() {
    prec = 1;
}
matrixSub::matrixSub() {
    prec = 1;
}
matrixDiv::matrixDiv() {
    prec = 1;
}
matrixAdd::matrixAdd() {
    prec = 1;
}

