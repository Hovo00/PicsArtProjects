#include "Matrix.h"

std::string Matrix::getTypename() const {
    return "matrix";
}

Matrix::Matrix(const std::string& str) {
    initMatrix(str);
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


void Matrix::initMatrix(const std::string& str) {
    _matrix.resize(str.size());
    _rowCount = 0;
    _colCount = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (std::isdigit(str[i]) || str[i] == '-') {
            std::string numb;
            while(i < str.size() && (std::isdigit(str[i]) || str[i] == '.' || str[i] == '-')) {
                numb.push_back(str[i++]);
            }
            _matrix[_rowCount].push_back(std::stof(numb));            
        }
        if (str[i] == '}') {
            ++_rowCount;
        }
    }
    _colCount = _matrix[0].size();
    --_rowCount;
    _matrix.resize(_rowCount);
}

void Matrix::printValue() const{
    for (auto &i : _matrix) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
