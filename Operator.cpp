#include "Operator.h"

std::shared_ptr<Operand> Operator::evaluate() {
    std::vector<std::shared_ptr<Operand> > vec;
    for (int i = 0; i < operandCount(); ++i) {
        vec.push_back(children[i]->evaluate());
    }
    std::reverse(vec.begin(), vec.end());

    return doOperation(vec);
}
int IbinOperations::operandCount() {
    return 2;
}
int IternOperations::operandCount() {
    return 3;
}
