#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <vector>
#include "Node.h"
#include "Matrix.h"

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
            if (node -> token->tokType == TokenType::Operand) {
                std::cout << "m" << " ";
            }
        inOrder(node->right);
    }
    Matrix evaluate(std::shared_ptr<Node>& node) {
        if (node->token->tokType == TokenType::Operator) {
            auto l = evaluate(node->left);
            auto r = evaluate(node->right);
            //node->token->doStuff(std::vector<Matrix>{node->left->token->doStuff(), node->right->token->doStuff()});
            return node->token->doStuff(std::vector<Matrix>{l, r});
        }
        return node->token->doStuff();
    }
public:
    std::shared_ptr<Node> head;
};

#endif