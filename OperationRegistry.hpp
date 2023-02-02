#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>


class Operand;

struct OperationSigniture {
    OperationSigniture(const std::string& operationName, const std::vector<std::string>& argumentsType);
    bool operator==(const OperationSigniture &other) const;
    const std::string operationName;
    const std::vector<std::string> argumentsType;
};

template<>
struct std::hash<OperationSigniture> {
    size_t operator()(const OperationSigniture& signiture) const {
        std::string key = signiture.operationName;
        for (int i = 0; i < signiture.argumentsType.size(); ++i) {
            key += signiture.argumentsType[i];
        }
        return std::hash<std::string>{}(key);
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
    using OperationHandler = std::function<std::shared_ptr<const Operand>(std::vector<std::shared_ptr<const Operand> >)>;
    using OverloadInfo = std::vector<std::vector<std::string> >;
    using OperationInfo = std::pair<OverloadInfo, OperationProperties>;
    using ReturnType = std::string;
    using HandlerInfo = std::pair<ReturnType, OperationHandler>;
public:
    void addOperator(const OperationSigniture& sign, const std::string& returnType, OperationHandler handler, int precedence, Associativity assoc, Notation note);
    void addFunction(const OperationSigniture& sign, const std::string& returnType, OperationHandler handler);
    void addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler conversion);

    HandlerInfo handlerInfo(const OperationSigniture& sign) const;
    const OperationInfo& operationInfo(const std::string& OperationHandler) const;
    const std::vector<std::string>& conversionInfo(const std::string& typeName) const;
public:
    bool areConvertableTypes(const std::string& operandType1, const std::string& operandType2) const;
    bool existSigniture(const OperationSigniture& sign) const;
    bool existOperation(const std::string& operationName) const;
private:
    std::unordered_map<std::string, std::vector<std::string> > _conversionInfo;
    std::unordered_map<OperationSigniture, HandlerInfo > _operationMap;
    std::unordered_map<std::string, OperationInfo> _operationInfo;
};

#endif
