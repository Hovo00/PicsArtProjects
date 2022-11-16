#ifndef TOKEN_H
#define TOKEN_H

enum class TokenType {Operator , Matrix, Function};

class Token {
public:
    TokenType tokType;
    virtual void doStuff() = 0;
    int prec;
};

#endif