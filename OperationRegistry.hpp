#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>


class Operand;

struct OperationKey {
    OperationKey(const std::string& operationName, const std::vector<std::string>& argumentsType);
    bool operator==(const OperationKey &other) const;
    const std::string operationName;
    const std::vector<std::string> argumentsType;
};

template<>
struct std::hash<OperationKey> {
    size_t operator()(const OperationKey& key) const {
        std::string finalKey = key.operationName;
        for (int i = 0; i < key.argumentsType.size(); ++i) {
            finalKey += key.argumentsType[i];
        }
        return std::hash<std::string>{}(finalKey);
    }
};

enum class Associativity {LeftToRight, RightToLeft};
enum class OperationType {Function, Operator};
// sin(30) prefix , (a + b) infix, (a == b) ? postfix
enum class Notation {Prefix, Infix, Postfix};

struct OperationProperties {
    OperationType operationType;
    int precedence;
    int argumentCount;
    Associativity associativity;
    Notation notation;
};


class OperationRegistry {
public:
    using OperandRef = std::shared_ptr<const Operand>;
    using OperationHandler = std::function<std::shared_ptr<const Operand>(std::vector<OperandRef>)>;
    using OverloadInfo = std::vector<std::vector<std::string> >;
    using OperationInfo = std::pair<OverloadInfo, OperationProperties>;
public:
    void addOperator(OperationHandler Operator, const OperationKey& key, int precedence, Associativity assoc, Notation note);
    void addFunction(OperationHandler Function, const OperationKey& key);
    void addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler convertion);

    OperandRef operate(const OperationKey& key, const std::vector<OperandRef >& operands) const;
    const OperationInfo& operationInfo(const std::string& OperationHandler) const;
public:
    bool areConvertableTypes(const std::string& operandType1, const std::string& operandType2) const;
    bool existKey(const OperationKey& key) const;
    bool existOperation(const std::string& operationName) const;
private:
    std::unordered_map<std::string, std::vector<std::string> > _conversionInfo;
    std::unordered_map<OperationKey, OperationHandler> _operationMap;
    std::unordered_map<std::string, OperationInfo> _operationInfo;
};

#endif
