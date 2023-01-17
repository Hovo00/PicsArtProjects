#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.hpp"
#include "OperationRegistry.hpp"

class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(const std::string& inputExpression, const OperationRegistry& registry) ;
private:
    VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression, const OperationRegistry& registry);
    void initializeVariables(VectorOfLexems& lexems, const OperationRegistry& registry);
    void inputVariable(VectorOfLexems& lexems, int lexemIndex, const OperationRegistry& registry);
private:
    bool isFunction(const std::string& expression, const OperationRegistry& registry);
    bool isOperator(const std::string& Operator, const OperationRegistry& registry);
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos,
                                        const OperationRegistry& registry) ;
    //can be variable , matrix or float
    void addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                          const OperationRegistry& registry) ;
    bool isValidMatrixSymbol(char symbol);

    void addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex, const OperationRegistry& registry);
    void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry);
    void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry);
    void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry);
    void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount, const OperationRegistry& registry);
    void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,const OperationRegistry& registry);
};

#endif
