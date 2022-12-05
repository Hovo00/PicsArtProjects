#include "Operand.h"

std::shared_ptr<Operand> Operand::evaluate() {
    return shared_from_this();
}