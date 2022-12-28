#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

class Operand;

enum class OperationType {Function, Operator};

struct OperationInfo {  
    OperationType operationType;
    int precedence;
    int argumentCount;
    std::string associativity;

    // sin(30) prefix , (a + b) infix, (a == b) ? postfix
    std::string notation;
};

class OperationRegistry {
public:
    using OPERAND = std::shared_ptr<Operand>;
    using FUNCTION = std::function<std::shared_ptr<Operand>(std::vector<OPERAND>)>;

    void addOperator(const std::string& operatorName, FUNCTION Operator, const std::string& key, int argCount,
                     int precedence, std::string associativity, std::string notation);
    void addFunction(const std::string& functionName, FUNCTION Function, const std::string& key, int argCount);
    void addOperatorOverload(const std::string& operatorName, FUNCTION Operator, const std::string& key);
    void addFunctionOverload(const std::string& functionName, FUNCTION Function, const std::string& key);

    OPERAND Operation(const std::string& key, const std::vector<OPERAND >& operands) const;
    OperationInfo operationInfo(const std::string& Operator) const;

public:
    bool isFunction(const std::string& expression) const;
    bool isOperator(const std::string& Operator) const;
    //int isOperator(const std::string& inputExpression, int pos) const;
    bool exist(const std::string& key) const;
public:
//remove
    bool isOperatorSymbol(char symbol) const;
private:
    void initializeOperationMap();
private:
    std::unordered_map<std::string, FUNCTION> _operationMap;
//remove
    std::vector<char> _operatorSymbols;
    std::unordered_map<std::string, OperationInfo> _operationTypeInfo;
};

#endif