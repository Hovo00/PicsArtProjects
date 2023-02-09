#include "CreatorFunctions.hpp"
#include "ConvertFunctions.hpp"

std::shared_ptr<Float> Creators::createFloat(const std::string& value) {
    return std::make_shared<Float>(ConvertFunctions::stringToFloat(value));
}
std::shared_ptr<Matrix> Creators::createMatrix(const std::string& value) {
    return std::make_shared<Matrix>(ConvertFunctions::stringToMatrix(value));
}

