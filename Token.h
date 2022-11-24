#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>
#include <memory>

enum class TokenType {Operator, Operand};

class Matrix;
class Operand;

class Token {
public:
    TokenType tokType;
    virtual Operand* doStuff(std::vector<Operand*> = {}) = 0;
    virtual int tokenData() = 0;
};

#endif