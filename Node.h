#ifndef NODE_H
#define NODE_H
#include <memory>
#include "Token.h"

class Node {
public:
    virtual Operand* evaluate() = 0;
};

#endif