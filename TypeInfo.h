#ifndef TYPEINFO_H
#define TYPEINFO_H
#include <vector>
#include <string>
#include <unordered_map>


class TypeInfo {
public:
    static bool isFunction(const std::string& expression);
    static int precedence(const std::string& oper);
    static int argumentCount(const std::string& oper);
    static void addOperator(const std::string&, int prec, int argCount);
    static void addFunction(const std::string&, int argCount);
public:
    static bool isOperatorSymbol(char symb);
    static bool isOperator(const std::string& Operator);
    static bool isValidMatrixSymbol(char symbol);
private:
    static std::unordered_map<std::string, int> _prec;
    static std::unordered_map<std::string, int> _argCount;
    static std::vector<char> _operatorSymbols;
    static std::vector<std::string> _operators;
    static std::vector<std::string> _functions;
};

#endif
