#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"
#include "TypeInfo.h"

class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    static VectorOfLexems divideTolexems(const std::string& inputExpression);
private:
    static VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression);
    static void initializeVariables(VectorOfLexems& lexems);
    static void inputVariable(VectorOfLexems& lexems, int lexemIndex);
private:
    static void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    static void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    static void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    static void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount);
    static void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    static void addNumberToMatrix(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);

};

#endif
