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
    Operand* evaluate(std::shared_ptr<Node>&); 
private:
    std::shared_ptr<Node> head;
};

#endif