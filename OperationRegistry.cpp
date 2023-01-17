#include "OperationRegistry.hpp"
#include "Exception.hpp"

OperationKey::OperationKey(const std::string& operName, const std::vector<std::string>& argName) : operationName(operName),
                                                                                                   argumentsType(argName) {

}

bool OperationKey::operator==(const OperationKey &otherKey) const {
    if (otherKey.operationName != this->operationName || otherKey.argumentsType.size() != this->argumentsType.size()) {
        return false;
    }
    for (int i = 0; i < otherKey.argumentsType.size(); ++i) {
        if (otherKey.argumentsType[i] != this->argumentsType[i]) {
            return false;
        }
    }
    return true;
}
void OperationRegistry::addOperator(Operation Operator, const OperationKey& key, int precedence, Associativity associativity, Notation notation) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add operator with already existing key");

    if (_operationInfo.find(key.operationName) != _operationInfo.end()) {
        if (_operationInfo.at(key.operationName).second.precedence != precedence ||
            _operationInfo.at(key.operationName).second.associativity != associativity ||
            _operationInfo.at(key.operationName).second.notation != notation) {
                //change Expression ||||
                throw EmptyExpression();
        }
        _operationMap[key] = Operator;
        _operationInfo[key.operationName].first.push_back(key.argumentsType);
        return;
    }
    int argc = key.argumentsType.size();
    _operationInfo[key.operationName].second = OperationProperties{OperationType::Operator, precedence, argc, associativity, notation};
    _operationMap[key] = Operator;
    _operationInfo[key.operationName].first.push_back(key.argumentsType);
    for (const auto & symbol : key.operationName) {
        if (std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) == _operatorSymbols.end()) {
            _operatorSymbols.push_back(symbol);
        }
    }
}
void OperationRegistry::addFunction(Operation Function, const OperationKey& key) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add function with already existing key");
    if (_operationInfo.find(key.operationName) != _operationInfo.end()) {
        _operationMap[key] = Function;
        _operationInfo[key.operationName].first.push_back(key.argumentsType);
    }
    _operationInfo[key.operationName].first.push_back(key.argumentsType);
    int argc = key.argumentsType.size();
    _operationInfo[key.operationName].second = OperationProperties{OperationType::Function, 10000, argc, Associativity::RightToLeft, Notation::Prefix};
    _operationMap[key] = Function;
}

bool OperationRegistry::existKey(const OperationKey& key) const{

    return (_operationMap.find(key) != _operationMap.end());
}

// bool OperationRegistry::isFunction(const std::string& expression) const {
//     return (_operationInfo.find(expression) != _operationInfo.end()
//             && _operationInfo.at(expression).second.operationType == OperationType::Function);
// }

bool OperationRegistry::isOperatorSymbol(char symbol) const {
    return std::find(_operatorSymbols.begin(), _operatorSymbols.end(), symbol) != _operatorSymbols.end();
}

OperationRegistry::OperandRef OperationRegistry::operate(const OperationKey& key, const std::vector<std::shared_ptr<const Operand> >& operands) const{

    return (OperationRegistry::_operationMap.at(key))(operands);
}

// bool OperationRegistry::isOperator(const std::string& Operator) const {
//     return _operationInfo.find(Operator) != _operationInfo.end();
// }
bool OperationRegistry::existOperation(const std::string& operationName) const{
    return _operationInfo.find(operationName) != _operationInfo.end();
}


const OperationRegistry::OperationInfo& OperationRegistry::operationInfo(const std::string& operationName) const{
    //add checks
    return _operationInfo.at(operationName);

}

void OperationRegistry::addConversion(const std::string& operandType1, const std::string& operandType2, Operation convertFunction) {
    //add checks
    _operationMap[OperationKey("conversion",std::vector<std::string>{operandType1, operandType2})] = convertFunction;
    _conversionInfo[operandType1].push_back(operandType2);
}
bool OperationRegistry::areConvertableTypes(const std::string& operandType1, const std::string& operandType2) const{
    if (_conversionInfo.find(operandType1) == _conversionInfo.end()) {
        return false;
    }
    auto convertableTypes = _conversionInfo.at(operandType1);
    return std::find(convertableTypes.begin(), convertableTypes.end(), operandType2) != convertableTypes.end();
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
