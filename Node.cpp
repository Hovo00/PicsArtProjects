#include "Node.h"
Node::Node(std::shared_ptr<Token> t, 
           std::shared_ptr<Node> l, 
           std::shared_ptr<Node> r) : token(t), left(l), right(r) {
            
           }
