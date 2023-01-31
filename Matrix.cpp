#include "Matrix.hpp"

std::string Matrix::getTypeName() const {
    return "matrix";
}

Matrix::Matrix(const std::vector<std::vector<double> >& matrix) : _matrix(matrix) {
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

const double& Matrix::at(int row, int col) const{
    //Add check for correct row and col count
    return _matrix[row][col];
}

double& Matrix::at(int row, int col) {
    return const_cast<double&>(const_cast<const Matrix*>(this)->at(row, col));
}

std::string Matrix::toString() const {
    std::string matrixStringRepresentation = "{";
    for (auto &i : _matrix) {
        matrixStringRepresentation.push_back('{');
        matrixStringRepresentation.push_back(' ');
        for (auto &j : i) {
            //for removing trailing zeroes
            std::stringstream number;
            number << j;

            matrixStringRepresentation += number.str();
            matrixStringRepresentation.push_back(' ');
        }
        matrixStringRepresentation.push_back('}');
        matrixStringRepresentation.push_back(' ');
    }
    matrixStringRepresentation.push_back('}');
    return matrixStringRepresentation;
}
