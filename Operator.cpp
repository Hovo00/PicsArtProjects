#include "Operator.h"

Operator::Operator(std::string operType, const std::vector<std::shared_ptr<Expression> >& args) : operatorType(operType),
                                                                                                  arguments(args){
}

std::string Operator::getTypename() const {
    return operatorType;
}

std::shared_ptr<Operand> Operator::evaluate() {
    std::vector<std::shared_ptr<Operand> > vec;
    for (int i = 0; i < TypeInfo::argCount[operatorType]; ++i) {
        vec.push_back(arguments[i]->evaluate());
    }
    std::reverse(vec.begin(), vec.end());
    std::cout << vec.size() << std::endl;
    return doOperation(vec);
}
std::shared_ptr<Operand> Operator::doOperation(const std::vector<std::shared_ptr<Operand> >& operands) const {
    std::string key = operatorType;
    for (auto & operand : operands) {
        key += operand->getTypename();
    }
    if (OperationRegistry::operMap.find(key) == OperationRegistry::operMap.end()) {
       throwInvalidArgumentsError(operands);
    }
    return OperationRegistry::operMap[key](operands);
}

void Operator::throwInvalidArgumentsError(const std::vector<std::shared_ptr<Operand> >& arguments) const{
    std::string errorMess = "operator ";
    errorMess += (operatorType + " unsupported for arguments of type ");
    for (auto& operand : arguments) {
        errorMess += operand->getTypename() + ", ";
    }
    throw UnsupportedOperatorArguments(errorMess);
}
