#ifndef TYPEINFO_H
#define TYPEINFO_H
#include <vector>
#include <string>
#include <unordered_map>

constexpr int HIGH_PREC = 5;

class TypeInfo {
public:
    static bool isReserved(const std::string&);
    static int operPrec(const std::string&);
    static bool addOperator(const std::string&, int, int);
    static bool addFunction(const std::string&, int);
public:
    static bool isLetter(char);
    static bool isSymbol(char);
    static bool isOperator(char);
    static bool isDigit(char);
    static bool isValidMatrixSymbol(char);
    static bool isValidNumber(std::string&, int);
public:
    static std::unordered_map<std::string, int> prec;
    static std::unordered_map<std::string, int> argCount;
private:
    static std::vector<std::string> operators;
    static std::vector<std::string> functions;
};

#endif