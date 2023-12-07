#ifndef TYPECONVERSIONFUNCTIONS_H
#define TYPECONVERSIONFUNCTIONS_H
#include "Float.hpp"
#include "Bool.hpp"


namespace TypeConversionFunctions {
    std::shared_ptr<const Operand> boolToFloat(const std::vector<std::shared_ptr<const Operand> >& arguments);
    std::shared_ptr<const Operand> FloatToBool(const std::vector<std::shared_ptr<const Operand> >& arguments);
};

#endif