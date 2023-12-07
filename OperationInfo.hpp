#ifndef OPERATION_INFO_HPP
#define OPERATION_INFO_HPP
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

struct Properties {
    Properties() = default;
    Properties(int precedence, Associativity associativity, Notation notation);
    int precedence;
    Associativity associativity;
    Notation notation;
};

struct OperationProperties : Properties {
    OperationProperties() = default;
    OperationProperties(Properties props, OperationType type, int argCount);
    OperationType operationType;
    int argumentCount;
};


#endif // OPERATION_INFO_HPP