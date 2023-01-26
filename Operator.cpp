#include "Operator.hpp"

Operator::Operator(std::string operType, const std::vector<std::shared_ptr<Expression> >& args) : _operatorName(operType),
                                                                                                  _arguments(args){
}

std::shared_ptr<const Operand> Operator::evaluate(const OperationRegistry& registry) const{
    std::vector<std::shared_ptr<const Operand> > vec;
    for (int i = 0; i < registry.operationInfo(_operatorName).second.argumentCount; ++i) {
        vec.push_back(_arguments[i]->evaluate(registry));
    }
    std::reverse(vec.begin(), vec.end());
    return doOperation(vec, registry);
}
std::shared_ptr<const Operand> Operator::doOperation(const std::vector<std::shared_ptr<const Operand> >& arguments, const OperationRegistry& registry) const {
    std::vector<std::string> argumentsType;
    for (auto & argument : arguments) {
        argumentsType.push_back(argument->getTypeName());
    }

    if (!registry.existSigniture(OperationSigniture(_operatorName, argumentsType))) {
        auto argumentsInfo = registry.operationInfo(_operatorName).first;
        for (const auto& collection : argumentsInfo) {
            int i = 0;
            std::vector<std::shared_ptr<const Operand> > convertedArguments;
            std::vector<std::string> convertedArgumentsType;
            for (const auto & argType : collection) {
                if (registry.areConvertableTypes(arguments[i]->getTypeName(), argType)) {
                    auto key = OperationSigniture("conversion", std::vector<std::string>{arguments[i]->getTypeName(), argType});
                    convertedArguments.push_back(registry.operate(key, std::vector<std::shared_ptr<const Operand> >{arguments[i]}));
                    convertedArgumentsType.push_back(argType);
                }
                else {
                    convertedArguments.push_back(arguments[i]);
                    convertedArgumentsType.push_back(arguments[i]->getTypeName());
                }
                if (registry.existSigniture(OperationSigniture(_operatorName, convertedArgumentsType))) {
                    return registry.operate(OperationSigniture(_operatorName, convertedArgumentsType), convertedArguments);
                }
                ++i;
            }
        }
        throw UnsupportedOperatorArguments(arguments, _operatorName, registry.operationInfo(_operatorName).first);
    }
    return registry.operate(OperationSigniture(_operatorName, argumentsType), arguments);
}
