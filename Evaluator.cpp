#include "Evaluator.hpp"

void Evaluator::buildExpressionTree(std::string& inputExpression) {
    auto lexems = _lexer.divideTolexems(inputExpression, _operationRegistry);
    std::stack<std::pair<std::shared_ptr<Expression>, std::string > > treeStack;
    for (const auto& lexem : lexems) {
        if (lexem.first == "oper") {
            std::vector<std::string> argumentsType;
            std::vector<std::shared_ptr<Expression> > arguments;
            for (int i = 0; i < _operationRegistry.operationInfo(lexem.second).second.argumentCount; ++i) {
                arguments.push_back(treeStack.top().first);
                argumentsType.push_back(treeStack.top().second);
                treeStack.pop();
            }
            std::reverse(argumentsType.begin(), argumentsType.end());
            auto res = makeExpression(lexem, arguments, argumentsType);
            treeStack.push(res);
        }
        else {
            treeStack.push(makeExpression(lexem));
        }
    }
    _head = treeStack.top().first;
    treeStack.pop();
}
void Evaluator::addOperator(const OperationSigniture& key, const std::string& returnType, OperationHandler Operator, int precedence, Associativity associativity, Notation notation) {
    _lexer.registerSymbols(key);
    if (key.argumentsType.size() > 2) {
        if (key.operationName.size() != key.argumentsType.size() - 1) {
            throw std::string("Characters count of Operator which have more then 2 arguments must be equal to argument count - 1");
        }
        _operationRegistry.addOperator(OperationSigniture(std::string{key.operationName.back()}, key.argumentsType), returnType, Operator, precedence, associativity, notation);
        return;
    }
    _operationRegistry.addOperator(key, returnType, Operator, precedence, associativity, notation);
}
void Evaluator::addFunction(const OperationSigniture& key, const std::string& returnType, OperationHandler Function) {
    _operationRegistry.addFunction(key, returnType, Function);
}
void Evaluator::addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler convertFunction) {
    _operationRegistry.addConversion(operandType1, operandType2, convertFunction);
}

std::pair<std::shared_ptr<Expression>, std::string> Evaluator::makeExpression(const std::pair<std::string, std::string>& lexem,
                                                                              const std::vector<std::shared_ptr<Expression> >& arguments,
                                                                              const std::vector<std::string>& argumentsType) {
    if (lexem.first == "oper") {
        for (auto & i : argumentsType) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    // if (!_operationRegistry.existSigniture(OperationSigniture(lexem.second, argumentsType))) {
    //     auto argumentsInfo = _operationRegistry.operationInfo(lexem.second).first;
    //     for (const auto& collection : argumentsInfo) {
    //         int i = 0;
    //         //std::vector<std::shared_ptr<const Operand> > convertedArguments;
    //         std::vector<std::string> convertedArgumentsType;
    //         for (const auto & argType : collection) {
    //             if (_operationRegistry.areConvertableTypes(argumentsType[i], argType)) {
    //                 auto key = OperationSigniture("conversion", std::vector<std::string>{argumentsType[i], argType});
    //                 //convertedArguments.push_back(_operationRegistry.handlerInfo(key).second(std::vector<std::shared_ptr<const Operand> >{arguments[i]}));
    //                 convertedArgumentsType.push_back(argType);
    //             }
    //             else {
    //                 //convertedArguments.push_back(arguments[i]);
    //                 convertedArgumentsType.push_back(argumentsType[i]);
    //             }
    //             if (_operationRegistry.existSigniture(OperationSigniture(lexem.second, convertedArgumentsType))) {
    //                 return _operationRegistry.handlerInfo(OperationSigniture(lexem.second, convertedArgumentsType)).second(convertedArguments);
    //             }
    //             ++i;
    //         }
    //     }
        //throw UnsupportedOperatorArguments(arguments, lexem.second, _operationRegistry.operationInfo(lexem.second).first);
    //}
        auto handlerInfo = _operationRegistry.handlerInfo(OperationSigniture{lexem.second, argumentsType});
        return std::make_pair(std::make_shared<Operator>(lexem.second, arguments, handlerInfo.second), handlerInfo.first);
    }
    else if (lexem.first == "matrix") {
        return std::make_pair(std::make_shared<Matrix>(ConvertFunctions::stringToMatrix(lexem.second)), lexem.first);
    }
    else if (lexem.first == "float") {
        return std::make_pair(std::make_shared<Float>(ConvertFunctions::stringToFloat(lexem.second)), lexem.first);
    }
    return std::make_pair(std::make_shared<Float>(0), "");
 }

 std::shared_ptr<const Operand> Evaluator::_evaluate(const std::shared_ptr<Expression>& head) const {
    return head->evaluate();
 }
 std::shared_ptr<const Operand> Evaluator::evaluate(std::string& inputExpression) {
    buildExpressionTree(inputExpression);
    return _evaluate(_head);
}
