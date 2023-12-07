#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <stack>
#include "Exception.hpp"
#include "OperationRegistry.hpp"


class Lexer {
public:
    using VectorOfLexems  = std::vector<std::pair<std::string, std::string> >;
    using OperandInfo = std::pair<std::string, std::function<std::string(const std::string&, int)> >;
    using Validator = std::function<std::string(const std::string&, int&) >;
    using Count = int;
public:
    VectorOfLexems divideTolexems(const std::string& inputExpression, const OperationRegistry& registry);
public:
    void registerSymbols(const OperationSigniture& key);
    void registerValidator(const std::string& operandName, Validator validator);
private:
    VectorOfLexems infixToPostfix(const OperationRegistry& registry);
    void initializeVariables(const OperationRegistry& registry);
    void inputVariable(int lexemIndex, const OperationRegistry& registry);
private:
    //can be variable or operand
    void addNegativeLexem(int& pos, int& lexemIndex, const OperationRegistry& registry);

    void addVariableToLexems(int& pos, int& lexemIndex, const OperationRegistry& registry);
    void addFunctionToLexems(int& pos, int& lexemCount, const OperationRegistry& registry);
    void addOperatorToLexems(int& pos, int& lexemIndex, const OperationRegistry& registry);
private:
    bool isSeparator(const std::string& expression) const;
    bool isFunction(const std::string& expression, const OperationRegistry& registry);
    bool isOperator(const std::string& op, const OperationRegistry& registry);
    bool isOperatorSymbol(char symbol) const;
    bool isMultiOperandOperator(const std::string& symbol);
private:
    int precedence(const std::string& operation, const OperationRegistry& registry);

    void updateCount(const std::string& symbol);
    int getCount(const std::string& symbol);
    std::string getSeparator(const std::string& symbol);
private:
    std::string _inputExpression;
    VectorOfLexems _lexems;
    std::vector<std::pair<std::string, Validator> > _operandValidators;
    std::vector<char> _symbolRegistry;
    std::vector<std::pair<std::string, Count> > _separatorRegistry;
};

#endif
