#include "Matrix.h"

Matrix::Matrix() {
    tokType = TokenType::Matrix;
}
Matrix::Matrix(const std::string& str) {
    tokType = TokenType::Matrix;
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
    --rowCount;
    matrix.resize(rowCount);
}
Matrix::Matrix(int row, int col) {
    tokType = TokenType::Matrix;
    rowCount = row;
    colCount = col;
    matrix.resize(row);
    for(auto & i : matrix) {
        i.resize(col);
    }
}


int Matrix::getColCount() const{
    return colCount;
}
int Matrix::getRowCount() const{
    return rowCount;
}
void Matrix::doStuff(){
        printMat();
}