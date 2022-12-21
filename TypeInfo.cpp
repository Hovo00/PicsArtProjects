#include "TypeInfo.h"

std::vector<std::string> TypeInfo::_operators = {"+", "-", "*", "/"};
std::vector<std::string> TypeInfo::_functions = {"select", "transpose", "inverse", "det", "sin", "cos"};
std::vector<char> TypeInfo::_operatorSymbols = {'+', '-', '*', '/', '=', '?', '!'};
bool TypeInfo::isFunction(const std::string& str) {
    return std::find(_functions.begin(), _functions.end(), str) != _functions.end();
}
int TypeInfo::precedence(const std::string& oper) {
    //add checks
    if (isFunction(oper)) {
        return _operators.size();
    }
    return _prec[oper];
}

int TypeInfo::argumentCount(const std::string& oper) {
    //add checks
    return _argCount[oper];
}
void TypeInfo::addOperator(const std::string& op, int argc, int precedence) {
    assert(std::find(_operators.begin(), _operators.end(), op) == _operators.end() && "trying to add existing operator");
    _operators.push_back(op);
    _prec[op] = precedence;
    _argCount[op] = argc;
}
void TypeInfo::addFunction(const std::string& func, int argc) {
    assert(std::find(_functions.begin(), _functions.end(), func) == _functions.end() && "trying to add existing function");
    _functions.push_back(func);
    _argCount[func] = argc;
}
std::unordered_map<std::string, int> TypeInfo::_argCount = {{"select", 3}, {"transpose", 1}, {"inverse", 1}, 
                                                           {"det", 1}, {"sin", 1},{"cos", 1}, {"+", 2}, {"-", 2}, {"*", 2}, {"/", 2}};

std::unordered_map<std::string, int> TypeInfo::_prec = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};//, {"(", HIGH_PREC}, {")", HIGH_PREC}};


bool TypeInfo::isOperatorSymbol(char symbol) {
    return std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) != _operatorSymbols.end();
}
bool TypeInfo::isOperator(const std::string& Operator) {
    return std::find(_operators.begin(), _operators.end(), Operator) != _operators.end();
}
bool TypeInfo::isValidMatrixSymbol(char i) {
        return (std::isdigit(i) || i == '{' || i == '}' || i == ' ' || i == '-');
}
