#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

class Operand;
struct OperationKey {
    OperationKey(const std::string& operationName, const std::vector<std::string>& argumentsName);
    bool operator==(const OperationKey &other) const;
    const std::string operationName;
    const std::vector<std::string> argumentsName;
};

template<>
struct std::hash<OperationKey> {
    size_t operator()(const OperationKey& key) const {
        std::string finalKey = key.operationName;
        for (int i = 0; i < key.argumentsName.size(); ++i) {
            finalKey += key.argumentsName[i];
        }
        return std::hash<std::string>{}(finalKey);
    }
};
enum class Associativity {LeftToRight, RightToLeft};
enum class OperationType {Function, Operator};
// sin(30) prefix , (a + b) infix, (a == b) ? postfix
enum class Notation {Prefix, Infix, Postfix};

struct OperationInfo {
    OperationType operationType;
    int precedence;
    int argumentCount;
    Associativity associativity;
    Notation notation;
};

class OperationRegistry {
public:
    using OPERAND = std::shared_ptr<const Operand>;
    using FUNCTION = std::function<std::shared_ptr<const Operand>(std::vector<OPERAND>)>;
    using ARGUMENTINFO = std::vector<std::vector<std::string> >;

    void addOperator(const std::string& operatorName, FUNCTION Operator, const OperationKey& key, int argCount,
                     int precedence, Associativity associativity, Notation notation);
    void addFunction(const std::string& functionName, FUNCTION Function, const OperationKey& key, int argCount);
    void addOperationOverload(const std::string& operationName, FUNCTION Operator, const OperationKey& key);
    void addConversion(const std::string& operandType1, const std::string& operandType2, FUNCTION convertFunction);

    //
    OPERAND operate(const OperationKey& key, const std::vector<OPERAND >& operands) const;
    OperationInfo operationInfo(const std::string& Operator) const;
    ARGUMENTINFO operationArgumentsInfo(const std::string& operation) const;
    std::vector<std::string> conversionInfo(const std::string& operandType) const;
public:
    bool isFunction(const std::string& expression) const;
    bool isOperator(const std::string& Operator) const;
    bool isConvertable(const std::string& operandType1, const std::string& operandType2) const;
    //int isOperator(const std::string& inputExpression, int pos) const;
    bool exist(const OperationKey& key) const;
public:
//remove
    bool isOperatorSymbol(char symbol) const;
private:
    void initializeOperationMap();
private:
    std::unordered_map<std::string, std::vector<std::string> > _conversionInfo;
    std::unordered_map<std::string , ARGUMENTINFO > _operationArgumentsInfo;

    std::unordered_map<OperationKey, FUNCTION> _operationMap;
    std::unordered_map<std::string, OperationInfo> _operationTypeInfo;
//remove
    std::vector<char> _operatorSymbols;
};

#endif
