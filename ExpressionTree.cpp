#include "ExpressionTree.h"

void ExpressionTree::buildExpressionTree(const ExpressionTree::VectorOfLexems& lexems) {
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (const auto& lexem : lexems) {
        if (lexem.first == "oper") {
            std::vector<std::shared_ptr<Expression> > arguments;
            for (int i = 0; i < TypeInfo::argumentCount(lexem.second); ++i) {
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

std::shared_ptr<Expression>& ExpressionTree::getHead() {
    return _head;
}
 std::shared_ptr<Expression> ExpressionTree::makeExpression(const std::pair<std::string, std::string>& lexem,
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
 }
 std::shared_ptr<Operand> ExpressionTree::evaluate(const std::shared_ptr<Expression>& head) {
    return head->evaluate();
 }