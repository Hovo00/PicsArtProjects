#ifndef TYPEINFO_H
#define TYPEINFO_H
#include <vector>
#include <string>
#include <unordered_map>


class TypeInfo {
public:
    static bool isReserved(const std::string& str);
    static int operPrec(const std::string& oper);
    static bool addOperator(const std::string&, int prec, int argCount);
    static bool addFunction(const std::string&, int argCount);
public:
    static bool isSymbol(char symb);
    static bool isOperator(char oper);
    static bool isValidMatrixSymbol(char symb);
public:
    static std::unordered_map<std::string, int> prec;
    static std::unordered_map<std::string, int> argCount;
private:
    static std::vector<std::string> operators;
    static std::vector<std::string> functions;
};

#endif
