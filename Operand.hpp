#ifndef OPERAND_H
#define OPERAND_H

#include "Expression.hpp"

class Operand : public Expression ,
                public std::enable_shared_from_this<Operand>{
public:
    std::shared_ptr<const Operand> evaluate(const OperationRegistry&) const override;
    virtual std::string toString() const = 0;
};

#endif