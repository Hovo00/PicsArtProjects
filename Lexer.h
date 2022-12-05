#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"
#include "TypeInfo.h"

class Lexer {
public:
    std::vector<std::string> divideTolexems(std::string& inpStr);
private:
    std::vector<std::string> infixToPostfix(std::vector<std::string>& infixExpression);
    std::vector<std::string> lexems;
    int lexemCount;
    void addNumberToLexems(std::string& inpStr, int& pos);
    void addVariableToLexems(std::string& inpStr, int& pos);
    void addMatrixToLexems(std::string& inpStr, int& pos);
    void addOperatorToLexems(std::string& inpStr, int& pos);
    void addNumberToMatrix(std::string& inpStr, int& pos);

};

#endif
