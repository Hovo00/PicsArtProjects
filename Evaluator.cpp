#include "Evaluator.hpp"
#include "OperationRegistry.hpp"

void Evaluator::buildExpressionTree(std::string& inputExpression) {
    auto lexems = _lexer.divideTolexems(inputExpression, _operationRegistry);
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (const auto& lexem : lexems) {
        if (lexem.first == "oper") {
            std::vector<std::shared_ptr<Expression> > arguments;
            for (int i = 0; i < _operationRegistry.operationInfo(lexem.second).second.argumentCount; ++i) {
                arguments.push_back(treeStack.top());
                treeStack.pop();
            }
            treeStack.push(makeExpression(lexem, arguments));
        }
        else {
            treeStack.push(makeExpression(lexem));
        }
    }
    _head = treeStack.top();
    treeStack.pop();
}
void Evaluator::addOperator(const OperationSigniture& key, OperationHandler Operator, int precedence, Associativity associativity, Notation notation) {
    _lexer.registerSymbols(key);
    if (key.argumentsType.size() > 2) {
        if (key.operationName.size() != key.argumentsType.size() - 1) {
            throw std::string("Characters count of Operator which have more then 2 arguments must be equal to argument count - 1");
        }
        _operationRegistry.addOperator(OperationSigniture(std::string{key.operationName.back()}, key.argumentsType), Operator, precedence, associativity, notation);
        return;
    }
    _operationRegistry.addOperator(key, Operator, precedence, associativity, notation);
}
void Evaluator::addFunction(const OperationSigniture& key, OperationHandler Function) {
    _operationRegistry.addFunction(key, Function);
}
void Evaluator::addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler convertFunction) {
    _operationRegistry.addConversion(operandType1, operandType2, convertFunction);
}

 std::shared_ptr<Expression> Evaluator::makeExpression(const std::pair<std::string, std::string>& lexem,
                                                            const std::vector<std::shared_ptr<Expression> >& arguments
                                                            ) {
    if (lexem.first == "oper") {
        return std::make_shared<Operator>(lexem.second, arguments);
    }
    if (lexem.first == "matrix") {
        return std::make_shared<Matrix>(ConvertFunctions::stringToMatrix(lexem.second));
    }
    if (lexem.first == "float") {
        return std::make_shared<Float>(ConvertFunctions::stringToFloat(lexem.second));
    }

    return std::make_shared<Float>(0);

 }

 std::shared_ptr<const Operand> Evaluator::_evaluate(const std::shared_ptr<Expression>& head) const {
    return head->evaluate(_operationRegistry);
 }
 std::shared_ptr<const Operand> Evaluator::evaluate(std::string& inputExpression) {
    buildExpressionTree(inputExpression);
    return _evaluate(_head);
}
