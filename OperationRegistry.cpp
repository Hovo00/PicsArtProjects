#include "OperationRegistry.hpp"
#include "Exception.hpp"

OperationSigniture::OperationSigniture(const std::string& operName, const std::vector<std::string>& argName) : operationName(operName),
                                                                                                   argumentsType(argName) {

}

bool OperationSigniture::operator==(const OperationSigniture &otherSigniture) const {
    if (otherSigniture.operationName != this->operationName || otherSigniture.argumentsType.size() != this->argumentsType.size()) {
        return false;
    }
    for (int i = 0; i < otherSigniture.argumentsType.size(); ++i) {
        if (otherSigniture.argumentsType[i] != this->argumentsType[i]) {
            return false;
        }
    }
    return true;
}
void OperationRegistry::addOperator(const OperationSigniture& key, OperationHandler Operator, int precedence, Associativity associativity, Notation notation) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add operator with already existing key");
    if (key.argumentsType.size() == 3 && key.operationName.size() == 2) {
        addOperator(OperationSigniture(":", key.argumentsType), Operator, precedence, associativity, notation);
        return;
    }
    if (_operationInfo.find(key.operationName) != _operationInfo.end()) {
        if (_operationInfo.at(key.operationName).second.precedence != precedence ||
            _operationInfo.at(key.operationName).second.associativity != associativity ||
            _operationInfo.at(key.operationName).second.notation != notation) {
                //change Exception ||||
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
}
void OperationRegistry::addFunction(const OperationSigniture& key, OperationHandler Function) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add function with already existing key");
    if (_operationInfo.find(key.operationName) != _operationInfo.end()) {
        _operationMap[key] = Function;
        _operationInfo[key.operationName].first.push_back(key.argumentsType);
    }
    _operationInfo[key.operationName].first.push_back(key.argumentsType);
    int argc = key.argumentsType.size();
    _operationInfo[key.operationName].second = OperationProperties{OperationType::Function, 10000, argc, Associativity::LeftToRight, Notation::Prefix};
    _operationMap[key] = Function;
}

bool OperationRegistry::existSigniture(const OperationSigniture& key) const{

    return (_operationMap.find(key) != _operationMap.end());
}

OperationRegistry::OperandRef OperationRegistry::operate(const OperationSigniture& key, const std::vector<std::shared_ptr<const Operand> >& operands) const{

    return (OperationRegistry::_operationMap.at(key))(operands);
}

bool OperationRegistry::existOperation(const std::string& operationName) const{
    return _operationInfo.find(operationName) != _operationInfo.end();
}


const OperationRegistry::OperationInfo& OperationRegistry::operationInfo(const std::string& operationName) const{
    if (_operationInfo.find(operationName) == _operationInfo.end()) {
        std::string message = "operationInfo not contain operation " + operationName;
        throw message;
    }
    return _operationInfo.at(operationName);
}

void OperationRegistry::addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler convertFunction) {
    _operationMap[OperationSigniture("conversion",std::vector<std::string>{operandType1, operandType2})] = convertFunction;
    _conversionInfo[operandType1].push_back(operandType2);
}
bool OperationRegistry::areConvertableTypes(const std::string& operandType1, const std::string& operandType2) const{
    if (_conversionInfo.find(operandType1) == _conversionInfo.end()) {
        return false;
    }
    auto convertableTypes = _conversionInfo.at(operandType1);
    return std::find(convertableTypes.begin(), convertableTypes.end(), operandType2) != convertableTypes.end();
}
