#include "Matrix.h"

Matrix::Matrix() {

}

Matrix::Matrix(const std::string& str) {
    initMatrix(str);
}

std::shared_ptr<Operand> Operand::evaluate() {
    return shared_from_this();
}

Matrix::Matrix(int row, int col) {
    //tokType = TokenType::Operand;
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
std::string Matrix::getInfo() {
    return "matrix";
}
void Matrix::printValue() {
    for (auto &i : matrix) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void Float::printValue() {
    std::cout << value;
}
