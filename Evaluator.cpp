#include "Evaluator.hpp"

Evaluator::Evaluator(const OperationRegistry& registry) : _operationRegistry(registry),
                                                                    _lexer(registry) {

}

void Evaluator::buildExpressionTree(std::string& inputExpression) {
    auto lexems = _lexer.divideTolexems(inputExpression);
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (const auto& lexem : lexems) {
        if (lexem.first == "oper") {
            std::vector<std::shared_ptr<Expression> > arguments;
            for (int i = 0; i < _operationRegistry.operationInfo(lexem.second).argumentCount; ++i) {
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

const std::shared_ptr<Expression>& Evaluator::getHead() const{
    return _head;
}
 std::shared_ptr<Expression> Evaluator::makeExpression(const std::pair<std::string, std::string>& lexem,
                                                            const std::vector<std::shared_ptr<Expression> >& arguments) {
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
