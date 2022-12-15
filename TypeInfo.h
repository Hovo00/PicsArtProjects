#ifndef TYPEINFO_H
#define TYPEINFO_H
#include <vector>
#include <string>
#include <unordered_map>


class TypeInfo {
public:
    static bool isReserved(const std::string& str);
    static int precedence(const std::string& oper);
    static int argumentCount(const std::string& oper);
    //static bool addOperator(const std::string&, int prec, int argCount);
    //static bool addFunction(const std::string&, int argCount);
public:
    static bool isSymbol(char symb);
    static bool isOperator(const std::string& inpStr, int pos);
    static bool isValidMatrixSymbol(char symbol);
private:
    static std::unordered_map<std::string, int> _prec;
    static std::unordered_map<std::string, int> _argCount;
    static std::vector<std::string> _operators;
    static std::vector<std::string> _functions;
};

#endif
