#include "Matrix.h"

Matrix::Matrix() {
    tokType = TokenType::Operand;
}
Matrix::Matrix(const std::string& str) {
    tokType = TokenType::Operand;
    initMatrix(str);
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

Matrix* Matrix::doStuff(std::vector<Operand*> vec){
    //printMat();
    return this;
}
void Matrix::printMat() {
    for (auto &i : matrix) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    //std::cout << std::endl << getColCount() << " " << getRowCount() << std::endl;
}
int Matrix::tokenData() {
    return 1;
}
void Matrix::printOperand() {
    printMat();
} 

bool Matrix::initMatrix(const std::string& str) {
    matrix.resize(str.size());
    rowCount = 0;
    colCount = 0;
    for (auto& i : str) {
        if (TypeInfo::isDigit(i)) {
            matrix[rowCount].push_back(i - '0');
        }
        if (i == '}') {
            ++rowCount;
        }
    }
    colCount = matrix[0].size();
    --rowCount;
    matrix.resize(rowCount);
    return true;
}
