#ifndef MATRMUL_H
#define MATRMUL_H

#include "Operator.h"

class matrixMul : public IbinMatOperations {
public:
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};

#endif