#ifndef FLOATOPERATIONS_H
#define FLOATOPERATIONS_H

#include <vector>
#include <memory>
#include <cmath>
#include "Float.hpp"
#include "Bool.hpp"

namespace FloatOperations {
    std::shared_ptr<const Operand> doubleAddition(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleSubtraction(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleMultiplication(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleDivision(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleInverse(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> doubleEqual(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> cosinus(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> sinus(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> thernardouble(const std::vector<std::shared_ptr<const Operand> >& arguments);
};

#endif