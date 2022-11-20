#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>

enum class TokenType {Operator, Operand};

class Matrix;

class Token {
public:
    TokenType tokType;
    virtual Matrix doStuff(std::vector<Matrix> = {}) = 0;
    int prec;
};

#endif