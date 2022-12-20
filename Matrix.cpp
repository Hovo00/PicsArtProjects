#include "Matrix.h"

std::string Matrix::getTypeName() const {
    return "matrix";
}

Matrix::Matrix(const std::vector<std::vector<float> >& matrix) : _matrix(matrix) {
    _colCount = matrix[0].size();
    _rowCount = matrix.size();
}

Matrix::Matrix(int row, int col) {
    _rowCount = row;
    _colCount = col;
    _matrix.resize(row);
    for (auto & i : _matrix) {
        i.resize(col);
    }
}

int Matrix::getColCount() const{
    return _colCount;
}
int Matrix::getRowCount() const{
    return _rowCount;
}

float& Matrix::at(int row, int col) {
    //Add check for correct row and col count
    return _matrix[row][col];
}

void Matrix::print() const{
    for (auto &i : _matrix) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
