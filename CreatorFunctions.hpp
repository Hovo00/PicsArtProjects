#ifndef CREATORSFUNCTIONS_HPP
#define CREATORSFUNCTIONS_HPP

#include <memory>
#include <iostream>
#include "Float.hpp"
#include "Matrix.hpp"
#include "ConvertFunctions.hpp"

namespace Creators {
    std::shared_ptr<Float> createFloat(const std::string& value);
    std::shared_ptr<Matrix> createMatrix(const std::string& value);
}

#endif