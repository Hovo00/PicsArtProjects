#include "ExpressionTree.h"

bool ExpressionTree::buildExpressionTree(std::vector<std::string > tokens) {
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (auto& token : tokens) {
        if (TypeInfo::isOperator(token[0])) {
            std::vector<std::shared_ptr<Expression> > arguments;
            std::string str;
            str.push_back(token[0]);
            for (int i = 0; i < TypeInfo::argCount[str]; ++i) {
                arguments.push_back(treeStack.top());
                treeStack.pop();
            }
            treeStack.push(makeExpression(token, arguments));
        }
        else {
            treeStack.push(makeExpression(token));
        }
    }
    head = treeStack.top();
    treeStack.pop(); 
    return true;
}

std::shared_ptr<Expression>& ExpressionTree::getHead() {
    return head;
}
 std::shared_ptr<Expression> ExpressionTree::makeExpression(std::string token, std::vector<std::shared_ptr<Expression> > arguments) {
    switch(token[0]) {
    case 'm' : return std::make_shared<Matrix>(token);
    case '+' : return std::make_shared<Operator>("+", arguments);
    case '-' : return std::make_shared<Operator>("-", arguments);
    case '*' : return std::make_shared<Operator>("*", arguments); 
    case 'n' : return std::make_shared<Float>(token); 
    }
 }
 std::shared_ptr<Operand> ExpressionTree::evaluate(std::shared_ptr<Expression>& head){
    OperationRegistry::initializeOperationMap();
    return head->evaluate();
 }