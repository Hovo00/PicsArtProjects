#include "Tree.h"

void Tree::BuildTree(std::vector<std::shared_ptr<Token> >& tokens) {
    std::stack<std::shared_ptr<Node> > treeStack;
    for (auto& token : tokens) {
        if (token->tokType == TokenType::Operand) {
            treeStack.push(std::make_shared<Node>(token));
        }
        else {
            auto right = treeStack.top();
            treeStack.pop();
            auto left = treeStack.top();
            treeStack.pop();

            treeStack.push(std::make_shared<Node>(token, left, right));
        }
    }
    head = treeStack.top();
    treeStack.pop();
}
std::shared_ptr<Node>& Tree::getHead() {
    return head;
}
