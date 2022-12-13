#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"
#include "TypeInfo.h"

class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(std::string& inputString);
private:
    VectorOfLexems infixToPostfix(VectorOfLexems& infixExpression);
    void initializeVariables();
    void inputVariable(int lexemIndex);
    VectorOfLexems lexems;
private:
    void addNumberToLexems(std::string& inpStr, int& pos, int lexemIndex);
    void addVariableToLexems(std::string& inpStr, int& pos, int lexemIndex);
    void addMatrixToLexems(std::string& inpStr, int& pos, int lexemIndex);
    void addFunctionToLexems(std::string& inpStr, int& pos, int& lexemCount);
    void addOperatorToLexems(std::string& inpStr, int& pos, int lexemIndex);
    void addNumberToMatrix(std::string& inpStr, int& pos, int lexemIndex);
};

#endif
