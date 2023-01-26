#include "FloatOperations.hpp"

std::shared_ptr<const Operand> FloatOperations::doubleAddition(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<const Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<const Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() + f2->getValue());
}
std::shared_ptr<const Operand> FloatOperations::doubleSubtraction(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<const Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<const Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() - f2->getValue());
}
std::shared_ptr<const Operand> FloatOperations::doubleMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<const Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<const Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() * f2->getValue());
}
std::shared_ptr<const Operand> FloatOperations::doubleDivision(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto f1 = std::static_pointer_cast<const Float>(arguments[0]);
    auto f2 = std::static_pointer_cast<const Float>(arguments[1]);
    return std::make_shared<Float>(f1->getValue() / f2->getValue());
}
std::shared_ptr<const Operand> FloatOperations::sinus(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto varFloat = std::static_pointer_cast<const Float>(arguments[0]);
    return std::make_shared<Float>(std::sin(varFloat->getValue() * M_PI / 180));
}
std::shared_ptr<const Operand> FloatOperations::cosinus(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto varFloat = std::static_pointer_cast<const Float>(arguments[0]);
    auto res = std::make_shared<Float>(std::cos(varFloat->getValue() * M_PI / 180));
    return res;
}
std::shared_ptr<const Operand> FloatOperations::doubleInverse(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto flt = std::static_pointer_cast<const Float>(arguments[0]);
    return std::make_shared<Float>(-flt->getValue());
}
std::shared_ptr<const Operand> FloatOperations::doubleEqual(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto flt1 = std::static_pointer_cast<const Float>(arguments[0]);
    auto flt2 = std::static_pointer_cast<const Float>(arguments[1]);
    return std::make_shared<Bool>(flt1->getValue() == flt2->getValue());
}
std::shared_ptr<const Operand> FloatOperations::thernardouble(const std::vector<std::shared_ptr<const Operand> >& arguments) {
    auto boolean = std::static_pointer_cast<const Bool>(arguments[0]);
    auto flt1 = std::static_pointer_cast<const Float>(arguments[1]);
    auto flt2 = std::static_pointer_cast<const Float>(arguments[2]);
    if (boolean->getValue()) {
        return std::make_shared<Float>(flt1->getValue());
    }
    return std::make_shared<Float>(flt2->getValue());
    return boolean->getValue() ? arguments[1] : arguments[2];
}