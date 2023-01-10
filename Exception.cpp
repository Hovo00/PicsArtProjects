#include "Exception.hpp"

UnsupportedOperatorArguments::UnsupportedOperatorArguments(const std::vector<std::shared_ptr<const Operand> >& args, const std::string& operType,
                                                           const std::vector<std::vector<std::string> >& candidateArgs) : arguments(args),
                                                                                                                         operatorType(operType),
                                                                                                                         candidateArguments(candidateArgs) {
}

char const* UnsupportedOperatorArguments::what() const noexcept {
    std::string errorMessage = "operator ";
    errorMessage += (operatorType + " unsupported for arguments of type ");
    for (const auto& operand : arguments) {
        errorMessage += operand->getTypeName() + ", ";
    }
    return errorMessage.data();
}

CustomException::CustomException(int col, const std::string& inputExpr) : column(col),
                                                                          inputExpression(inputExpr) {

}

InvalidMatrixOperand::InvalidMatrixOperand(int col, const std::string& inputExp) : CustomException(col, inputExp) {

}

char const* InvalidMatrixOperand::what() const noexcept {
    std::string errorMessage = "Invalid symbol in matrix brackets in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.c_str();
}

InvalidVariable::InvalidVariable(int col, const std::string& inputExp) : CustomException(col, inputExp){

}

char const* InvalidVariable::what() const noexcept {
    std::string errorMessage = "Invalid Variable (ambiguity number or variable ) in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}

invalidSyntax::invalidSyntax(int col, const std::string& inputExp) : CustomException(col, inputExp){

}
char const* invalidSyntax::what() const noexcept {
    std::string errorMessage = "Invalid Syntax at col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}

WrondMatrixDimension::WrondMatrixDimension(int col, int prev, int curr, const std::string& inputExp) : CustomException(col, inputExp) ,
                                                                                                previous(prev), current(curr) {

}

char const* WrondMatrixDimension::what() const noexcept {
    std::string errorMessage = " Invalid column count : ";
    errorMessage += std::to_string(current) + " at column " + std::to_string(column) + " previous defined " + std::to_string(previous);
    return errorMessage.data();
}
