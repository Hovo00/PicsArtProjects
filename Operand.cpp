#include "Operand.hpp"

std::shared_ptr<const Operand> Operand::evaluate(const OperationRegistry&) const{
    return shared_from_this();
}