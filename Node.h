#ifndef NODE_H
#define NODE_H
#include <memory>

class Node {
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Token token;
};

#endif