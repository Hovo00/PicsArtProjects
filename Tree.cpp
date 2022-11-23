#include "Tree.h"

void Tree::BuildTree(std::vector<std::shared_ptr<Token> >& tokens) {
    std::stack<std::shared_ptr<Node> > treeStack;
    for (auto& token : tokens) {
        if (token->tokType == TokenType::Operand) {
            treeStack.push(std::make_shared<Node>(token));
        }
        else {
            std::vector<std::shared_ptr<Node> > childs;
            for (int i = 0; i < token->tokenData(); ++i) {
                childs.push_back(treeStack.top());
                treeStack.pop();
        }
            treeStack.push(std::make_shared<Node>(token, childs));
        }
    }
    head = treeStack.top();
    treeStack.pop();
}

Operand* Tree::evaluate(std::shared_ptr<Node>& node) {
    if (node->token->tokType == TokenType::Operator) {
        std::vector<Operand> vec;
        for (auto& ch : node->childs) {
            vec.push_back(*(evaluate(ch)));
            std::reverse(vec.begin(), vec.end());
        }
        return node->token->doStuff(vec);
    }
    return node->token->doStuff();
}

std::shared_ptr<Node>& Tree::getHead() {
    return head;
}
