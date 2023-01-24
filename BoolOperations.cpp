#include "BoolOperations.hpp"

std::shared_ptr<const Operand> BoolOperations::questionMarkBool(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto boolean = std::static_pointer_cast<const Bool>(arguments[0]);
    return std::make_shared<Bool>(boolean->getValue());
}