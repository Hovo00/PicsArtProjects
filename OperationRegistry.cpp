#include "OperationRegistry.h"

void OperationRegistry::addOperator(const std::string& operatorName, FUNCTION Operator, const std::string& key, int argCount,
                                    int precedence, std::string associativity, std::string notation) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add operator with already existing key");
    assert(_operationTypeInfo.find(operatorName) == _operationTypeInfo.end() && "trying to add existing operator");
    _operationTypeInfo[operatorName] = OperationInfo{OperationType::Operator, precedence, argCount, associativity, notation};
    _operationMap[key] = Operator;
    for (const auto & symbol : operatorName) {
        if (std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) == _operatorSymbols.end()) {
            _operatorSymbols.push_back(symbol);
        }
    }
}
void OperationRegistry::addFunction(const std::string& functionName, FUNCTION Function, const std::string& key, int argc) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add function with already existing key");
    assert(_operationTypeInfo.find(functionName) == _operationTypeInfo.end() && "trying to add existing operator");
    _operationTypeInfo[functionName] = OperationInfo{OperationType::Function, 10000, argc, "leftToRight", "prefix"};
    _operationMap[key] = Function;
}


bool OperationRegistry::exist(const std::string& key) const{

    return (_operationMap.find(key) != _operationMap.end());
}

OperationInfo OperationRegistry::operationInfo(const std::string& Operation) const {
    return _operationTypeInfo.at(Operation);
}

bool OperationRegistry::isFunction(const std::string& expression) const {
    return (_operationTypeInfo.find(expression) != _operationTypeInfo.end() 
            && _operationTypeInfo.at(expression).operationType == OperationType::Function);
}

bool OperationRegistry::isOperatorSymbol(char symbol) const {
    return std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) != _operatorSymbols.end();
}

OperationRegistry::OPERAND OperationRegistry::Operation(const std::string& key, const std::vector<std::shared_ptr<Operand> >& operands) const{
    return (OperationRegistry::_operationMap.at(key))(operands);
}

bool OperationRegistry::isOperator(const std::string& Operator) const {
    return _operationTypeInfo.find(Operator) != _operationTypeInfo.end();
}

// int OperationRegistry::isOperator(const std::string& inputExpression, int pos) const {
//     //int startPosition = pos;
//     std::string Operator;
//     int matchingOperatorsCount = _operationTypeInfo.size();
//     while (pos < inputExpression.size() && matchingOperatorsCount > 1){
//     matchingOperatorsCount = 0;
//     Operator.push_back(inputExpression[pos++]);
//     for (const auto & operation : _operationTypeInfo) {
//         if (operation.first.find(Operator, 0) != std::string::npos) {
//             ++matchingOperatorsCount;
//         }
//     }
//     }
//     if (matchingOperatorsCount == 1) {
//         return pos;
//     }
//     return 0;
// }


void OperationRegistry::addOperatorOverload(const std::string& operatorName, FUNCTION Operator, const std::string& key) {
    assert(!exist(key) && "trying to overload not existing operator");
    _operationMap[key] = Operator;
}
void OperationRegistry::addFunctionOverload(const std::string& functionName, FUNCTION Function, const std::string& key) {
    assert(!exist(key) && "trying to overload not existing function");
    _operationMap[key] = Function;
}
