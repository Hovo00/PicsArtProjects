#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include "Functions.h"


class OperationRegistry {
public:
    using OPERAND = std::shared_ptr<Operand>;
    using FUNCTION = std::function<std::shared_ptr<Operand>(std::vector<OPERAND>)>;
    static void addOperator(const std::string& operatorName, FUNCTION Operator, const std::string& key, int argCount, int precedence);
    static void addFunction(const std::string& functionName, FUNCTION Function, const std::string& key, int argCount);
    static void addOperatorOverload(const std::string& operatorName, FUNCTION Operator, const std::string& key);
    static void addFunctionOverload(const std::string& functionName, FUNCTION Function, const std::string& key);
    static OPERAND Operation(const std::string& key, const std::vector<OPERAND >& operands);
    static bool exist(const std::string& key);
private:
    static std::unordered_map<std::string, FUNCTION> _operationMap;
};

#endif