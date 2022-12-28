#include "FloatOperations.h"

std::shared_ptr<Operand> FloatOperations::floatAddition(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() + f2->getValue());
}
std::shared_ptr<Operand> FloatOperations::floatSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() - f2->getValue());
}
std::shared_ptr<Operand> FloatOperations::floatMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() * f2->getValue());
}
std::shared_ptr<Operand> FloatOperations::floatDivision(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() / f2->getValue());
}
std::shared_ptr<Operand> FloatOperations::sinus(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto varFloat = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Float>(std::sin(varFloat->getValue() * 3.14159 / 180));
}
std::shared_ptr<Operand> FloatOperations::cosinus(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto varFloat = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Float>(std::cos(varFloat->getValue() * 3.14159 / 180));
}
std::shared_ptr<Operand> FloatOperations::floatInverse(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto flt = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Float>(-flt->getValue());
}
std::shared_ptr<Operand> FloatOperations::floatEqual(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto flt1 = std::static_pointer_cast<Float>(arguments[0]);
    auto flt2 = std::static_pointer_cast<Float>(arguments[1]);
    return std::make_shared<Bool>(flt1->getValue() == flt2->getValue());
}
std::shared_ptr<Operand> FloatOperations::questionMarkFloat(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto flt = std::static_pointer_cast<Float>(arguments[0]);
    return std::make_shared<Bool>(flt->getValue() != 0);
}
std::shared_ptr<Operand> FloatOperations::thernarfloat(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto boolean = std::static_pointer_cast<Bool>(arguments[0]);
    auto flt1 = std::static_pointer_cast<Float>(arguments[1]);
    auto flt2 = std::static_pointer_cast<Float>(arguments[2]);
    if (boolean->getValue()) {
        return std::make_shared<Float>(flt1->getValue());
    }
    return std::make_shared<Float>(flt2->getValue());
}