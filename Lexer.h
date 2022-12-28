#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"
#include "OperationRegistry.h"

class Lexer {
public:
    Lexer(const OperationRegistry& operationRegistry);
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(const std::string& inputExpression);
private:
    VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression);
    void initializeVariables(VectorOfLexems& lexems);
    void inputVariable(VectorOfLexems& lexems, int lexemIndex);
private:
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos);
    //can be variable , matrix or float 
    void addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex);
    bool isValidMatrixSymbol(char symbol) const;

    void addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex);
    void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int lexemIndex);
    void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount);
    void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex);
private:
    const OperationRegistry& _operationRegistry;
};

#endif
