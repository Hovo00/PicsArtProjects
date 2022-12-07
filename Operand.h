#ifndef OPERAND_H
#define OPERAND_H

#include "Expression.h"

class Operand : public Expression ,
                public std::enable_shared_from_this<Operand>{
public:
    std::shared_ptr<Operand> evaluate() override;
    virtual void printValue() const = 0;
};

#endif