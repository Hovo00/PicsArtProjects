#include "Evaluator.hpp"
#include "OperationInfo.hpp"
#include "OperationRegistry.hpp"

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
            std::reverse(arguments.begin(), arguments.end());
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
void Evaluator::addOperator(const OperationSigniture& key, const std::string& returnType, OperationHandler Operator, Properties properties) {
    _lexer.registerSymbols(key);
    if (key.argumentsType.size() > 2) {
        if (key.operationName.size() != key.argumentsType.size() - 1) {
            throw std::string("Characters count of Operator which have more then 2 arguments must be equal to argument count - 1");
        }
        _operationRegistry.addOperator(OperationSigniture(std::string{key.operationName.back()}, key.argumentsType), returnType, Operator, properties);
        return;
    }
    _operationRegistry.addOperator(key, returnType, Operator, properties);
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

        if (!_operationRegistry.existSigniture(OperationSigniture(lexem.second, argumentsType))) {
            auto candidateSignitures = _operationRegistry.operationInfo(lexem.second).first;
            for (const auto& candidateSigniture : candidateSignitures) {
                int i = 0;
                std::vector<std::shared_ptr<Expression> > convertedArguments;
                std::vector<std::string> convertedArgumentsType;
                for (const auto & argType : candidateSigniture) {
                    if (_operationRegistry.areConvertableTypes(argumentsType[i], argType)) {
                        auto key = OperationSigniture("conversion", std::vector<std::string>{argumentsType[i], argType});
                        auto castHandler = _operationRegistry.handlerInfo(key).second;
                        convertedArguments.push_back(std::make_shared<Operator>("conversion", std::vector<std::shared_ptr<Expression> >{arguments[i]}, castHandler));
                        convertedArgumentsType.push_back(argType);
                    }
                    else {
                        convertedArguments.push_back(arguments[i]);
                        convertedArgumentsType.push_back(argumentsType[i]);
                    }
                    if (_operationRegistry.existSigniture(OperationSigniture(lexem.second, convertedArgumentsType))) {
                        auto handler = _operationRegistry.handlerInfo(OperationSigniture(lexem.second, convertedArgumentsType));
                        return std::make_pair(std::make_shared<Operator>(lexem.second, convertedArguments, handler.second), handler.first);
                    }
                    ++i;
                }
            }
            throw UnsupportedOperatorArguments(lexem.second, argumentsType, candidateSignitures);
        }
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
