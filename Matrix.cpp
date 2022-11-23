#include "Matrix.h"

Matrix::Matrix() {
    tokType = TokenType::Operand;
}
Matrix::Matrix(const std::string& str) {
    tokType = TokenType::Operand;
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
    tokType = TokenType::Operand;
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
Matrix* Matrix::doStuff(std::vector<Matrix> vec){
    printMat();
    return this;
}
void Matrix::printMat() {
    for (auto &i : matrix) {
        std::cout << std::endl;
        for (auto &j : i) {
            std::cout << j << " ";
        }
    }
    std::cout << std::endl << getColCount() << " " << getRowCount() << std::endl;
}
int Matrix::tokenData() {
    return 1;
}
void Matrix::printOperand() {
    printMat();
} 