#ifndef EXCEPTIONXX_H
#define EXCEPTIONXX_H

#include <exception>
#include <string>
#include <vector>

#include "Operand.h"

class UnsupportedOperatorArguments : public std::exception {
public:
    UnsupportedOperatorArguments(const std::vector<std::shared_ptr<const Operand> >& arguments, const std::string& operatorType, 
                                 const std::vector<std::vector<std::string> >& candidateArguments);
    char const* what() const noexcept override;
private:
    std::vector<std::shared_ptr<const Operand> > arguments;
    std::string operatorType;
    std::vector<std::vector<std::string> > candidateArguments;
};

class CustomException : public std::exception {
public:
    CustomException(int column, const std::string& inputExpression);
    const int column;
    const std::string inputExpression;
};

class InvalidMatrixOperand : public CustomException {
public:
    InvalidMatrixOperand(int column, const std::string& inputExpression);
    char const* what() const noexcept override;
};

class InvalidVariable : public CustomException {
public:
    InvalidVariable(int cl, const std::string& inputExpression);
    char const* what() const noexcept override;
};

class invalidSyntax : public CustomException {
public:
    invalidSyntax(int cl, const std::string& inputExpression);
    char const* what() const noexcept override;
};

class WrondMatrixDimension : public CustomException {
public:
    WrondMatrixDimension(int column, int previous, int current, const std::string& inputExpression);
    char const* what() const noexcept override;
    const int previous;
    const int current;
};

#endif
