#ifndef FLOATOPERATIONS_H
#define FLOATOPERATIONS_H

#include <vector>
#include <memory>
#include <cmath>
#include "Float.h"
#include "Bool.h"

namespace FloatOperations {
    std::shared_ptr<Operand> floatAddition(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatSubtraction(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatMultiplication(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatDivision(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatInverse(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> floatEqual(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> questionMarkFloat(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> cosinus(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> sinus(const std::vector<std::shared_ptr<Operand> >& arguments);
    std::shared_ptr<Operand> thernarfloat(const std::vector<std::shared_ptr<Operand> >& arguments);
};

#endif