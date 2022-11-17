#ifndef NODE_H
#define NODE_H
#include <memory>
#include "Token.h"

class Node {
public:
    Node(std::shared_ptr<Token> t = nullptr, std::shared_ptr<Node> l = nullptr ,std::shared_ptr<Node> r = nullptr);
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Token> token;
};

#endif