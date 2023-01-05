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

const float& Matrix::at(int row, int col) const{
    //Add check for correct row and col count
    return _matrix[row][col];
}

float& Matrix::at(int row, int col) {
    return const_cast<float&>(const_cast<const Matrix*>(this)->at(row, col));

}


void Matrix::print() const{
    std::cout << '{';
    for (auto &i : _matrix) {
        std::cout << '{' << ' ';
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << "}";
    }
    std::cout << '}' << std::endl;
}
