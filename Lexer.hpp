#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.hpp"
#include "OperationRegistry.hpp"

class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    VectorOfLexems divideTolexems(const std::string& inputExpression, const OperationRegistry& registry) const;
private:
    VectorOfLexems infixToPostfix(const VectorOfLexems& infixExpression, const OperationRegistry& registry) const;
    void initializeVariables(VectorOfLexems& lexems, const OperationRegistry& registry) const;
    void inputVariable(VectorOfLexems& lexems, int lexemIndex, const OperationRegistry& registry) const;
private:
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos,
                                        const OperationRegistry& registry) const;
    //can be variable , matrix or float
    void addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                          const OperationRegistry& registry) const;
    bool isValidMatrixSymbol(char symbol) const;

    void addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex,
                                const OperationRegistry& registry) const;
    void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry) const;
    void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry) const;
    void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry) const;
    void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount,
                                const OperationRegistry& registry) const;
    void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry) const;
};

#endif
