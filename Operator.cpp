#include "Operator.h"

Operator::Operator() {
    tokType = TokenType::Operator;
}
Matrix* IbinMatOperations::doStuff(std::vector<Operand*> vec) {
    auto first = static_cast<Matrix*>(vec[0]);
    auto second = static_cast<Matrix*>(vec[1]);
    return do_operation(*first, *second);
}

Matrix* IternMatOperations::doStuff(std::vector<Operand*> vec) {
    auto first = static_cast<Matrix*>(vec[0]);
    auto second = static_cast<Matrix*>(vec[1]);
    auto third = static_cast<Matrix*>(vec[2]);
    return do_operation(*first, *second, *third);
}
int IternMatOperations::tokenData() {
    return 3;
}
int IbinMatOperations::tokenData() {
    return 2;
}