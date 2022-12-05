#include "ExpressionTree.h"

bool ExpressionTree::buildExpressionTree(std::vector<std::string > tokens) {
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (auto& token : tokens) {
        if (TypeInfo::isOperator(token[0])) {
            std::vector<std::shared_ptr<Expression> > children;
            std::string str;
            str.push_back(token[0]);
            for (int i = 0; i < TypeInfo::argCount[str]; ++i) {
                children.push_back(treeStack.top());
                treeStack.pop();
            }
            treeStack.push(makeExpression(token, children));
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
 std::shared_ptr<Expression> ExpressionTree::makeExpression(std::string token, std::vector<std::shared_ptr<Expression> > children) {
    switch(token[0]) {
    case 'm' : return std::make_shared<Matrix>(token);
    case '+' : return std::make_shared<Add>(children);
    case '-' : return std::make_shared<Sub>(children);
    case '*' : return std::make_shared<Mul>(children); 
    case 'n' : return std::make_shared<Float>(token); 
    case 'v' : return std::make_shared<Matrix>();
    }
    return std::make_shared<Add>();
 }
 std::shared_ptr<Operand> ExpressionTree::evaluate(std::shared_ptr<Expression> head) {
    return head->evaluate();
    
 }

// {{2 2} {1 1} {2 2}} * { { 2   2}    {  1   1  } }
// {{2 2 } {1 1} } * {{1 2} {3 3d}}
