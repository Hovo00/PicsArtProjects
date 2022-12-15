#include "TypeInfo.h"

std::vector<std::string> TypeInfo::_operators = {"+", "-", "*", "=", "/", "(", ")"};
std::vector<std::string> TypeInfo::_functions = {"select", "transpose", "inverse", "det", "sin", "cos"};
bool TypeInfo::isReserved(const std::string& str) {
    return std::find(_functions.begin(), _functions.end(), str) != _functions.end();
}
int TypeInfo::precedence(const std::string& oper) {
    //add checks
    if (isReserved(oper)) {
        return _operators.size();
    }
    return _prec[oper];
}

int TypeInfo::argumentCount(const std::string& oper) {
    //add checks
    return _argCount[oper];
}
// bool TypeInfo::addOperator(const std::string& op, int argc, int precedence) {
//     operators.push_back(op);
//     prec[op] = precedence;
//     argCount[op] = argc;
//     return true;
// }
// bool TypeInfo::addFunction(const std::string& func, int argc) {
//     functions.push_back(func);
//     argCount[func] = argc;
//     return true;
// }
std::unordered_map<std::string, int> TypeInfo::_argCount = {{"select", 3}, {"transpose", 1}, {"inverse", 1}, 
                                                           {"det", 1}, {"sin", 1},{"cos", 1}, {"+", 2}, {"-", 2}, {"*", 2}, {"/", 2}};

std::unordered_map<std::string, int> TypeInfo::_prec = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};//, {"(", HIGH_PREC}, {")", HIGH_PREC}};


bool TypeInfo::isSymbol(char symb) {
    return (symb == '{'|| symb == '}' || symb == '.' || symb == '+' || symb == '=' || symb == '*' || symb == '-' || symb == ')' || symb == '(');
}
bool TypeInfo::isOperator(const std::string& inpStr, int pos) {
    //change in feuture if there will be more then one character operators
    std::string op;
    op.push_back(inpStr[pos]);
    return std::find(_operators.begin(), _operators.end(), op) != _operators.end();
}
bool TypeInfo::isValidMatrixSymbol(char i) {
        return (std::isdigit(i) || i == '{' || i == '}' || i == ' ' || i == '-');
}


