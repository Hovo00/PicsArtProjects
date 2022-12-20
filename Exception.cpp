#include "Exception.h"

UnsupportedOperatorArguments::UnsupportedOperatorArguments(const std::vector<std::shared_ptr<Operand> >& args,
                                                           const std::string& operType) : arguments(args),
                                                                                          operatorType(operType) {

}

char const* UnsupportedOperatorArguments::what() const noexcept {
    std::string errorMessage = "operator ";
    errorMessage += (operatorType + " unsupported for arguments of type ");
    for (const auto& operand : arguments) {
        errorMessage += operand->getTypeName() + ", ";
    }
    return errorMessage.data();
}

customException::customException(int col, const std::string& inputExpr) : column(col),
                                                                  inputExpression(inputExpr) {

}

invalidMatrixOperand::invalidMatrixOperand(int col, const std::string& inputExp) : customException(col, inputExp) {

}

char const* invalidMatrixOperand::what() const noexcept { 
    std::string errorMessage = "Invalid symbol in matrix brackets in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.c_str();
}

invalidVariable::invalidVariable(int col, const std::string& inputExp) : customException(col, inputExp){

}

char const* invalidVariable::what() const noexcept {
    std::string errorMessage = "Invalid Variable (ambiguity number or variable ) in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}
invalidSyntax::invalidSyntax(int col, const std::string& inputExp) : customException(col, inputExp){
   
}
char const* invalidSyntax::what() const noexcept {
    std::string errorMessage = "Invalid Syntax at col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}
wrondMatrixDimension::wrondMatrixDimension(int col, int prev, int curr, const std::string& inputExp) : customException(col, inputExp) ,
                                                                                                previous(prev), current(curr) {

}
char const* wrondMatrixDimension::what() const noexcept {
    std::string errorMessage = " Invalid column count : ";
    errorMessage += std::to_string(current) + " at column " + std::to_string(column) + " previous defined " + std::to_string(previous);
    return errorMessage.data();
}
