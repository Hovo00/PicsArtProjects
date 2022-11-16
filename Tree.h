#ifndef TREE_H
#define TREE_H

#include <stack>
#include "Node.h"

class Tree {
public:
    void BuildTree(std::vector<Token*>&);
private:
    std::shared_ptr<Node> head;
};

#endif