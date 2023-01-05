#ifndef TYPECONVERSIONFUNCTIONS_H
#define TYPECONVERSIONFUNCTIONS_H
#include "Float.h"
#include "Bool.h"


namespace TypeConversionFunctions {
    std::shared_ptr<const Operand> boolToFloat(const std::vector<std::shared_ptr<const Operand> >& arguments);
};

#endif