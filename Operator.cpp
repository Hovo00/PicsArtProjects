#include "Operator.h"

Operator::Operator(std::string operType, const std::vector<std::shared_ptr<Expression> >& args) : _operatorType(operType),
                                                                                                  _arguments(args){
}

std::string Operator::getTypeName() const {
    return _operatorType;
}

std::shared_ptr<Operand> Operator::evaluate(const OperationRegistry& registry) {
    std::vector<std::shared_ptr<Operand> > vec;
    for (int i = 0; i < registry.operationInfo(_operatorType).argumentCount; ++i) {
        vec.push_back(_arguments[i]->evaluate(registry));
    }
    std::reverse(vec.begin(), vec.end());
    return doOperation(vec, registry);
}
std::shared_ptr<Operand> Operator::doOperation(const std::vector<std::shared_ptr<Operand> >& operands,
                                               const OperationRegistry& registry) const {
    std::string key = _operatorType;
    for (auto & operand : operands) {
        key += operand->getTypeName();
    }

    if (!registry.exist(key)) {
        throw UnsupportedOperatorArguments(operands, _operatorType);
    }
    return registry.Operation(key, operands);
}
