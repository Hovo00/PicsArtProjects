#include "TypeInfo.h"

std::vector<std::string> TypeInfo::operators = {"+", "-", "*", "=", "(", ")"};
std::vector<std::string> TypeInfo::functions = {"select", "transpose", "inverse", "det", "sin", "cos"};
bool TypeInfo::isReserved(const std::string& str) {
    return std::find(functions.begin(), functions.end(), str) != functions.end();
}
int TypeInfo::operPrec(const std::string& oper) {
    if (isReserved(oper)) {
        return 3;
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
                                                           {"det", 1}, {"sin", 1},{"cos", 1}, {"+", 2}, {"-", 2}, {"*", 2}};

std::unordered_map<std::string, int> TypeInfo::prec = {{"+", 1}, {"-", 1}, {"*", 2}};//, {"(", HIGH_PREC}, {")", HIGH_PREC}};


bool TypeInfo::isSymbol(char symb) {
    return (symb == '{'|| symb == '}' || symb == '.' || symb == '+' || symb == '=' || symb == '*' || symb == '-' || symb == ')' || symb == '(') ? true : false;
}
bool TypeInfo::isOperator(const std::string& inpStr, int pos) {
    //change in feuture if there will be more then one character operators
    std::string op;
    op.push_back(inpStr[pos]);
    //
    return std::find(operators.begin(), operators.end(), op) != operators.end();
}
bool TypeInfo::isValidMatrixSymbol(char i) {
        return (std::isdigit(i) || i == '{' || i == '}' || i == ' ' || i == '-');
}

