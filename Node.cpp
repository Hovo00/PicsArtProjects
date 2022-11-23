#include "Node.h"
Node::Node(std::shared_ptr<Token> t, 
    std::vector<std::shared_ptr<Node> > ch) : token(t), childs(ch) {
}
