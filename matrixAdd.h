#ifndef MATRADD_H
#define MATRADD_H

#include "Operator.h"

class matrixAdd : public IbinMatOperations {
public:
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};

#endif