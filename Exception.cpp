#include "Exception.h"

void customException::showErrorPlace() const {
    std::cout << std::endl;
    for (int i = 0; i < col; ++i) {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;
    std::cout << inpStr << std::endl;
}

invalidMatrixOperand::invalidMatrixOperand(int cl, std::string inpStr) {
    col = cl;
    this->inpStr = inpStr;

}
char const* invalidMatrixOperand::what() const noexcept { 
    customException::showErrorPlace() ;
    return "Invalid symbol in matrix brackets in col : ";
}
invalidVariable::invalidVariable(int cl, std::string inpStr) {
    col = cl;
    this->inpStr = inpStr;
}
char const* invalidVariable::what() const noexcept {
    showErrorPlace();
    return " Invalid Variable (ambiguity number or variable ) in col : ";
}
invalidSyntax::invalidSyntax(int cl, std::string inpStr) {
    col = cl;
    this->inpStr = inpStr;

}
char const* invalidSyntax::what() const noexcept {
    showErrorPlace();
    return " Invalid Syntax  col : ";
}
wrondMatrixDimension::wrondMatrixDimension(int cl, int prv, int crr, std::string inpStr) {
    prev = prv;
    curr = crr;
    col = col;
    this->inpStr = inpStr;

}
char const* wrondMatrixDimension::what() const noexcept {
    return " Invalid column count : ";
}