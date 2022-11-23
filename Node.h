#ifndef NODE_H
#define NODE_H
#include <memory>
#include "Token.h"

class Node {
public:
    Node(std::shared_ptr<Token> = nullptr, std::vector<std::shared_ptr<Node> > = {});
public:
    std::vector<std::shared_ptr<Node> > childs;
    std::shared_ptr<Token> token;
};

#endif