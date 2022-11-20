#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "Token.h"

class Matrix : public Token {
public:
    Matrix();
    Matrix(int row, int col);
    Matrix(const std::string&);
    int getColCount() const;
    int getRowCount() const;
    virtual Matrix doStuff(std::vector<Matrix>) override;
    void printMat() {
        for (auto &i : matrix) {
            std::cout << std::endl;
            for (auto &j : i) {
                std::cout << j << " ";
            }
        }
    }
    bool is_digit(char digit) {
    return (digit <= '9' && digit >= '1') ? true : false;
}
private:
    int rowCount;
    int colCount;
    public:
    std::vector<std::vector<double>> matrix;
};

#endif