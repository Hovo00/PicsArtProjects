#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <vector>
#include "Node.h"

class Tree {
public:
    void BuildTree(std::vector<std::shared_ptr<Token> >&);
    std::shared_ptr<Node>& getHead();
    void inOrder(std::shared_ptr<Node>& node) {
        if ((node == nullptr)) {
            return;
        }
        inOrder(node->left);
         if (node -> token->tokType == TokenType::Operator) {
                std::cout << "o" << node ->token->prec << " ";
            }
            if (node -> token->tokType == TokenType::Matrix) {
                std::cout << "m" << " ";
            }
        inOrder(node->right);
    }
public:
    std::shared_ptr<Node> head;
};

#endif