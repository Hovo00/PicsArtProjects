#include "Matrix.h"

std::string Matrix::getTypename() const {
    return "matrix";
}

Matrix::Matrix(const std::string& str) {
    initMatrix(str);
}

Matrix::Matrix(int row, int col) {
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

bool Matrix::initMatrix(const std::string& str) {
    matrix.resize(str.size());
    rowCount = 0;
    colCount = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (std::isdigit(str[i]) || str[i] == '-') {
            std::string numb;
            while(std::isdigit(str[i]) || str[i] == '.' || str[i] == '-') {
                numb.push_back(str[i++]);
            }
            matrix[rowCount].push_back(std::stof(numb));            
        }
        if (str[i] == '}') {
            ++rowCount;
        }
    }
    colCount = matrix[0].size();
    --rowCount;
    matrix.resize(rowCount);
    return true;
}

void Matrix::printValue() const{
    for (auto &i : matrix) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

