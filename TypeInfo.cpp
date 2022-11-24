#include "TypeInfo.h"

std::vector<std::string> TypeInfo::operators = {"+", "-", "*", "="};
std::vector<std::string> TypeInfo::functions = {"select", "transpose", "inverse"};
bool TypeInfo::isReserved(const std::string& str) {
    // for (auto& item : operators) {
    //     if (str == item) {
    //         return true;
    //     }
    // }
    for (auto& item : functions) {
        if (str == item) {
            return true;
        }
    }
    return false;
}
int TypeInfo::operPrec(const std::string& oper) {
    if (isReserved(oper)) {
        return HIGH_PREC;
    }
    return prec[oper];
}
bool TypeInfo::addOperator(const std::string& op, int argc, int precedence) {
    operators.push_back(op);
    prec[op] = precedence;
    argCount[op] = argc;
    return true;
}
bool TypeInfo::addFunction(const std::string& func, int argc) {
    functions.push_back(func);
    argCount[func] = argc;
    return true;
}
std::unordered_map<std::string, int> TypeInfo::argCount = {{"select", 3}, {"transpose", 1}, {"inverse", 1}, 
                                                            {"+", 2}, {"-", 2}, {"*", 2}};

std::unordered_map<std::string, int> TypeInfo::prec = {{"+", 1}, {"-", 1}, {"*", 2}};//, {"(", HIGH_PREC}, {")", HIGH_PREC}};

bool TypeInfo::isLetter(char lett) {
    return (lett <= 'z' && lett >= 'A')  ? true : false;
}
bool TypeInfo::isSymbol(char symb) {
    return (symb == '{'|| symb == '}' || symb == ',') ? true : false;
}
bool TypeInfo::isOperator(char oper) {
    return (oper == '+' || oper == '-' || oper == '/' || oper == '*' || oper == '(' || oper == ')') ? true : false;
}
bool TypeInfo::isDigit(char digit) {
    return (digit <= '9' && digit >= '1') ? true : false;
}
//oper == '(' || oper == ')'