#include "OperationRegistry.hpp"

OperationKey::OperationKey(const std::string& operName, const std::vector<std::string>& argName) : operationName(operName),
                                                                                                   argumentsName(argName) {

}

bool OperationKey::operator==(const OperationKey &otherKey) const {
    if (otherKey.operationName != this->operationName || otherKey.argumentsName.size() != this->argumentsName.size()) {
        return false;
    }
    for (int i = 0; i < otherKey.argumentsName.size(); ++i) {
        if (otherKey.argumentsName[i] != this->argumentsName[i]) {
            return false;
        }
    }
    return true;
}
void OperationRegistry::addOperator(const std::string& operatorName, Operation Operator, const OperationKey& key, int argCount,
                                    int precedence, Associativity associativity, Notation notation) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add operator with already existing key");
    assert(_operationTypeInfo.find(operatorName) == _operationTypeInfo.end() && "trying to add existing operator");
    _operationTypeInfo[operatorName] = OperationInfo{OperationType::Operator, precedence, argCount, associativity, notation};
    _operationMap[key] = Operator;
    _operationArgumentsInfo[operatorName].push_back(key.argumentsName);
    for (const auto & symbol : operatorName) {
        if (std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) == _operatorSymbols.end()) {
            _operatorSymbols.push_back(symbol);
        }
    }
}
void OperationRegistry::addFunction(const std::string& functionName, Operation Function, const OperationKey& key, int argc) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add function with already existing key");
    assert(_operationTypeInfo.find(functionName) == _operationTypeInfo.end() && "trying to add existing operator");
    _operationArgumentsInfo[functionName].push_back(key.argumentsName);
    _operationTypeInfo[functionName] = OperationInfo{OperationType::Function, 10000, argc, Associativity::RightToLeft, Notation::Prefix};
    _operationMap[key] = Function;
}

bool OperationRegistry::exist(const OperationKey& key) const{

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

OperationRegistry::OperandRef OperationRegistry::operate(const OperationKey& key, const std::vector<std::shared_ptr<const Operand> >& operands) const{

    return (OperationRegistry::_operationMap.at(key))(operands);
}

bool OperationRegistry::isOperator(const std::string& Operator) const {
    return _operationTypeInfo.find(Operator) != _operationTypeInfo.end();
}

OperationRegistry::ArgumentInfo OperationRegistry::operationArgumentsInfo(const std::string& operation) const{
    //add checks
    return _operationArgumentsInfo.at(operation);

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

void OperationRegistry::addOperationOverload(const std::string& operationName, Operation Operator, const OperationKey& key) {
    assert(!exist(key) && "trying to overload not existing operation");
    _operationMap[key] = Operator;
    _operationArgumentsInfo[operationName].push_back(key.argumentsName);
}

std::vector<std::string>  OperationRegistry::conversionInfo(const std::string& operandType) const{
    //add checks
    return _conversionInfo.at(operandType);
}
void OperationRegistry::addConversion(const std::string& operandType1, const std::string& operandType2, Operation convertFunction) {
    //add checks
    _operationMap[OperationKey("conversion",std::vector<std::string>{operandType1, operandType2})] = convertFunction;
    _conversionInfo[operandType1].push_back(operandType2);
}
bool OperationRegistry::isConvertable(const std::string& operandType1, const std::string& operandType2) const{
    if (_conversionInfo.find(operandType1) == _conversionInfo.end()) {
        return false;
    }
    auto convertableTypes = _conversionInfo.at(operandType1);
    return std::find(convertableTypes.begin(), convertableTypes.end(), operandType2) != convertableTypes.end();
}


