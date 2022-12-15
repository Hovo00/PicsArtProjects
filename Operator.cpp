#include "Operator.h"

Operator::Operator(std::string operType, const std::vector<std::shared_ptr<Expression> >& args) : _operatorType(operType),
                                                                                                  _arguments(args){
}

std::string Operator::getTypename() const {
    return _operatorType;
}

std::shared_ptr<Operand> Operator::evaluate() {
    std::vector<std::shared_ptr<Operand> > vec;
    for (int i = 0; i < TypeInfo::argumentCount(_operatorType); ++i) {
        vec.push_back(_arguments[i]->evaluate());
    }
    std::reverse(vec.begin(), vec.end());
    return doOperation(vec);
}
std::shared_ptr<Operand> Operator::doOperation(const std::vector<std::shared_ptr<Operand> >& operands) const {
    std::string key = _operatorType;
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
    errorMess += (_operatorType + " unsupported for arguments of type ");
    for (auto& operand : arguments) {
        errorMess += operand->getTypename() + ", ";
    }
    throw UnsupportedOperatorArguments(errorMess);
}
