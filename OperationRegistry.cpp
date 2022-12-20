#include "OperationRegistry.h"


void OperationRegistry::addOperator(const std::string& oper, FUNCTION Operator, const std::string& key, int argc, int precedence) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add operator with already existing key");
    TypeInfo::addOperator(oper, argc, precedence);
    _operationMap[key] = Operator;
}
void OperationRegistry::addFunction(const std::string& func, FUNCTION Function, const std::string& key, int argc) {
    assert(_operationMap.find(key) == _operationMap.end() && "error , trying add function with already existing key");
    TypeInfo::addFunction(func, argc);
    _operationMap[key] = Function;
}


std::unordered_map<std::string, OperationRegistry::FUNCTION> OperationRegistry::_operationMap = {{"+matrixmatrix", Functions::matrixAddition}, 
                                                                                            {"-matrixmatrix", Functions::matrixSubtraction},
                                                                                            {"*matrixmatrix", Functions::matrixMultiplication},
                                                                                            {"+floatfloat", Functions::floatAddition},
                                                                                            {"-floatfloat", Functions::floatSubtraction},
                                                                                            {"*floatfloat", Functions::floatMultiplication},
                                                                                            {"inversematrix", Functions::matrixInverse},
                                                                                            {"detmatrix", Functions::matrixDeterminant},
                                                                                            {"transposematrix", Functions::matrixTranspose},
                                                                                            {"sinfloat", Functions::sinus},
                                                                                            {"cosfloat", Functions::cosinus},
                                                                                            {"selectmatrixmatrixmatrix", Functions::Select},
                                                                                            {"/floatfloat", Functions::floatDivision},
                                                                                            {"/matrixfloat", Functions::matrixFloatDivision}
};

bool OperationRegistry::exist(const std::string& key) {

    return (_operationMap.find(key) != _operationMap.end());
}

OperationRegistry::OPERAND OperationRegistry::Operation(const std::string& key, const std::vector<std::shared_ptr<Operand> >& operands) {
    return OperationRegistry::_operationMap[key](operands);
}

void OperationRegistry::addOperatorOverload(const std::string& operatorName, FUNCTION Operator, const std::string& key) {
    assert(!exist(key) && "trying to overload not existing operator");
    _operationMap[key] = Operator;
}
void OperationRegistry::addFunctionOverload(const std::string& functionName, FUNCTION Function, const std::string& key) {
    assert(!exist(key) && "trying to overload not existing function");
    _operationMap[key] = Function;
}
    

