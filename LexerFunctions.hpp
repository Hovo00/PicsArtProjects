#ifndef LEXER_FUNCTIONS_HPP
#define LEXER_FUNCTIONS_HPP

#include <sstream>
#include <stack>
#include <utility>
#include "Exception.hpp"
#include "OperationRegistry.hpp"

namespace LexerFunctions {
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos,
                                        const OperationRegistry& registry);
    //can be variable , matrix or float
    void addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                          const OperationRegistry& registry);
    bool isValidMatrixSymbol(char symbol);

    void addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex,
                                const OperationRegistry& registry);
    void addNumberToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry);
    void addVariableToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry);
    void addMatrixToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry);
    void addFunctionToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemCount,
                                const OperationRegistry& registry);
    void addOperatorToLexems(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex,
                                const OperationRegistry& registry);
    bool isNumber(const std::string& inputExpression, const VectorOfLexems& lexems, int pos, int lexemIndex,
                                const OperationRegistry& registry);
    bool isMatrix(const std::string& inputExpression, const VectorOfLexems& lexems, int pos, int lexemIndex,
                                const OperationRegistry& registry);
    bool isOperator(const std::string& inputExpression, const VectorOfLexems& lexems, int pos, int lexemIndex,
                                const OperationRegistry& registry);
};

#endif