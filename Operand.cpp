#include "Operand.h"

std::shared_ptr<Operand> Operand::evaluate(const OperationRegistry&) {
    return shared_from_this();
}