#ifndef FLOATOPERATIONS_H
#define FLOATOPERATIONS_H

#include <vector>
#include <memory>
#include <cmath>
#include "Float.h"
#include "Bool.h"

namespace FloatOperations {
    std::shared_ptr<const Operand> floatAddition(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> floatSubtraction(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> floatMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> floatDivision(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> floatInverse(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> floatEqual(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> questionMarkFloat(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> cosinus(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> sinus(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> thernarfloat(const std::vector<std::shared_ptr<const Operand> >& arguments);
};

#endif