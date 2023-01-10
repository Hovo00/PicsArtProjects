#include "Operator.hpp"

Operator::Operator(std::string operType, const std::vector<std::shared_ptr<Expression> >& args) : _operatorType(operType),
                                                                                                  _arguments(args){
}

std::string Operator::getTypeName() const {
    return _operatorType;
}

std::shared_ptr<const Operand> Operator::evaluate(const OperationRegistry& registry) const{
    std::vector<std::shared_ptr<const Operand> > vec;
    for (int i = 0; i < registry.operationInfo(_operatorType).argumentCount; ++i) {
        vec.push_back(_arguments[i]->evaluate(registry));
    }
    std::reverse(vec.begin(), vec.end());
    return doOperation(vec, registry);
}
std::shared_ptr<const Operand> Operator::doOperation(const std::vector<std::shared_ptr<const Operand> >& arguments,
                                               const OperationRegistry& registry) const {
    std::vector<std::string> argumentsType;
    //std::string key = _operatorType;
    for (auto & argument : arguments) {
        argumentsType.push_back(argument->getTypeName());
    }

    if (!registry.exist(OperationKey(_operatorType, argumentsType))) {
        auto argumentsInfo = registry.operationArgumentsInfo(_operatorType);
        for (const auto& collection : argumentsInfo) {
            int i = 0;
            std::vector<std::shared_ptr<const Operand> > convertedArguments;
            std::vector<std::string> convertedArgumentsType;
            for (const auto & argType : collection) {
                if (registry.isConvertable(arguments[i]->getTypeName(), argType)) {
                    auto key = OperationKey("conversion", std::vector<std::string>{arguments[i]->getTypeName(), argType});
                    convertedArguments.push_back(registry.operate(key, std::vector<std::shared_ptr<const Operand> >{arguments[i]}));
                    convertedArgumentsType.push_back(argType);
                }
                else {
                    convertedArguments.push_back(arguments[i]);
                    convertedArgumentsType.push_back(arguments[i]->getTypeName());
                }
                if (registry.exist(OperationKey(_operatorType, convertedArgumentsType))) {
                    return registry.operate(OperationKey(_operatorType, convertedArgumentsType), convertedArguments);
                }
                ++i;
            }
        }
        throw UnsupportedOperatorArguments(arguments, _operatorType, registry.operationArgumentsInfo(_operatorType));
    }
    return registry.operate(OperationKey(_operatorType, argumentsType), arguments);
}
