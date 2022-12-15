#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"
#include "TypeInfo.h"

class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(const std::string& inputExpression);
private:
    VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression);
    void initializeVariables();
    void inputVariable(int lexemIndex);
private:
    void addNumberToLexems(const std::string& inputExpression, int& pos, int lexemIndex);
    void addVariableToLexems(const std::string& inputExpression, int& pos, int lexemIndex);
    void addMatrixToLexems(const std::string& inputExpression, int& pos, int lexemIndex);
    void addFunctionToLexems(const std::string& inputExpression, int& pos, int& lexemCount);
    void addOperatorToLexems(const std::string& inputExpression, int& pos, int lexemIndex);
    void addNumberToMatrix(const std::string& inputExpression, int& pos, int lexemIndex);
private:
    VectorOfLexems lexems;
};

#endif
