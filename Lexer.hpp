#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.hpp"
#include "OperationRegistry.hpp"

class Lexer {
public:
    Lexer(const OperationRegistry& operationRegistry);
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(const std::string& inputExpression) const;
private:
    VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression) const;
    void initializeVariables(VectorOfLexems& lexems) const;
    void inputVariable(VectorOfLexems& lexems, int lexemIndex) const;
private:
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos) const;
    //can be variable , matrix or double
    void addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const;
    bool isValidMatrixSymbol(char symbol) const;

    void addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex) const;
    void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const;
    void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const;
    void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const;
    void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount) const;
    void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const;
private:
    const OperationRegistry& _operationRegistry;
};

#endif
