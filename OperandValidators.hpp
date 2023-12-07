#ifndef OPERANDVALIDATORS_HPP
#define OPERANDVALIDATORS_HPP
#include <vector>
#include <stack>
#include "Exception.hpp"
#include "OperationRegistry.hpp"

namespace Validators {

    std::string validateFloat(const std::string& inputExpression, int& pos);
    std::string validateMatrix(const std::string& inputExpression, int& pos);
    bool isValidMatrixSymbol(char symbol);
    std::string cutNumberFromExpression(const std::string& inputExpression, int& pos);

};

#endif