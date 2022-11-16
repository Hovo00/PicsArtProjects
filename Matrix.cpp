#include "Matrix.h"

Matrix::Matrix() {
    tokType = TokenType::Matrix;
}
Matrix::Matrix(const std::string& str) {
    matrix.resize(str.size());
    rowCount = 0;
    colCount = 0;
    for (auto& i : str) {
        if (is_digit(i)) {
            matrix[rowCount].push_back(i - '0');
        }
        if (i == '}') {
            ++rowCount;
        }
    }
    colCount = matrix[0].size();
    matrix.resize(rowCount);
}

int Matrix::getColCount() {
    return colCount;
}
int Matrix::getRowCount() {
    return rowCount;
}