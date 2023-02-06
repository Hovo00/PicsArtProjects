#include "Operator.hpp"

Operator::Operator(std::string operType,
                   const std::vector<std::shared_ptr<Expression> >& args,
                   OperationHandler handler) : _operatorName(operType),
                                               _arguments(args),
                                               _handler(handler) {
}

std::shared_ptr<const Operand> Operator::evaluate() const{
    std::vector<std::shared_ptr<const Operand> > args;
    for (int i = 0; i < _arguments.size(); ++i) {
        args.push_back(_arguments[i]->evaluate());
    }
    return _handler(args);
}
