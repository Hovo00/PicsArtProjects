#ifndef MATRSUB_H
#define MATRSUB_H

#include "Operator.h"

class matrixSub : public IbinMatOperations {
public:
    virtual Matrix* do_operation(const Matrix&, const Matrix&) override;
};

#endif