#include "Exception.h"

UnsupportedOperatorArguments::UnsupportedOperatorArguments(const std::string& message) :errorMessage(message) {

}

customException::customException(int col, std::string inputExpr) : column(col),
                                                                  inputExpression(inputExpr) {

}
char const* UnsupportedOperatorArguments::what() const noexcept {
    return errorMessage.data();
}

invalidMatrixOperand::invalidMatrixOperand(int col, std::string inputExp) : customException(col, inputExp) {

}

char const* invalidMatrixOperand::what() const noexcept { 
    std::string errorMessage = "Invalid symbol in matrix brackets in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.c_str();
}

invalidVariable::invalidVariable(int col, std::string inputExp) : customException(col, inputExp){

}

char const* invalidVariable::what() const noexcept {
    std::string errorMessage = "Invalid Variable (ambiguity number or variable ) in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}
invalidSyntax::invalidSyntax(int col, std::string inputExp) : customException(col, inputExp){
   
}
char const* invalidSyntax::what() const noexcept {
    std::string errorMessage = "Invalid Syntax at col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}
wrondMatrixDimension::wrondMatrixDimension(int col, int prev, int curr, std::string inputExp) : customException(col, inputExp) ,
                                                                                                previous(prev), current(curr) {

}
char const* wrondMatrixDimension::what() const noexcept {
    std::string errorMessage = " Invalid column count : ";
    errorMessage += std::to_string(current) + " at column " + std::to_string(column) + " previous defined " + std::to_string(previous);
    return errorMessage.data();
}
