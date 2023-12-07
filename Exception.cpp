#include "Exception.hpp"
#include "OperationRegistry.hpp"
#include <string>

UnsupportedOperatorArguments::UnsupportedOperatorArguments(const std::string& operationType,
                                                           const std::vector<std::string>& argTypes,
                                                           const std::vector<std::vector<std::string> >& candidateArgTypes) : _operationType(operationType),
                                                                                                                              _argTypes(argTypes),
                                                                                                                              _candidateArgTypes(candidateArgTypes) {
}

//revisit
char const* UnsupportedOperatorArguments::what() const noexcept {
    _errorMessage = "operation ";
    _errorMessage += (_operationType + " unsupported for arguments of type ");
    for (const auto& argType: _argTypes) {
        _errorMessage += argType + " ";
    }
    _errorMessage += "\n\nCandidate arguments are \n  ";

    for (const auto& candidates : _candidateArgTypes) {
        for (const auto& argType : candidates) {
            _errorMessage += argType + " ";
        }
        _errorMessage += "\n  ";
    }
    return _errorMessage.data();
}

CustomException::CustomException(int col, const std::string& inputExpr) : column(col),
                                                                          inputExpression(inputExpr) {

}

InvalidMatrixOperand::InvalidMatrixOperand(int col, const std::string& inputExp) : CustomException(col, inputExp) {

}

char const* InvalidMatrixOperand::what() const noexcept {
    errorMessage = "Invalid symbol in matrix brackets in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.c_str();
}

InvalidVariable::InvalidVariable(int col, const std::string& inputExp) : CustomException(col, inputExp){

}

char const* InvalidVariable::what() const noexcept {
    errorMessage = "Invalid Variable (ambiguity number or variable ) in col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}

invalidSyntax::invalidSyntax(int col, const std::string& inputExp) : CustomException(col, inputExp){

}
char const* invalidSyntax::what() const noexcept {
    errorMessage = "Invalid Syntax at col : ";
    errorMessage += std::to_string(column);
    return errorMessage.data();
}

WrondMatrixDimension::WrondMatrixDimension(int col, int prev, int curr, const std::string& inputExp) : CustomException(col, inputExp) ,
                                                                                                previous(prev), current(curr) {

}

char const* WrondMatrixDimension::what() const noexcept {
    errorMessage = " Invalid column count : ";
    errorMessage += std::to_string(current) + " at column " + std::to_string(column) + " previous defined " + std::to_string(previous);
    return errorMessage.data();
}


char const* EmptyExpression::what() const noexcept {
    errorMessage = " Enter not empty expression";
    return errorMessage.data();
}

// invalidTernar::invalidTernar(VectorOfLexems inputExpression,
//                              int ternSymblCount,
//                              const std::pair<std::string, std::string> ternarySymbols): ternSymbolCount(ternSymblCount),
//                                                                                         inputExpression(inputExpr),
//                                                                                         ternarSymbols(ternarySymbols) {
// }
// char const* invalidTernar::what() const noexcept override {
//     if (ternSymbolCount < 0) {
//         errorMessage = "l";
//         for (int i = inputExpr.size(); i > 0; --i) {
//             if (inputExpression[i].second == ternarSymbols.second) {
//                 errorMessage = "Redudant ternary symbol " + ternarSymbol.second + "at column " + std::to_string(i);
//                 return errorMessage;
//             }
//         }
//         return errorMessage;
//     }
// }


