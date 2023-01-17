#ifndef EXCEPTIONXX_HPP
#define EXCEPTIONXX_HPP

#include <exception>
#include <string>
#include <vector>
#include "Operand.hpp"

class UnsupportedOperatorArguments : public std::exception {
public:
    UnsupportedOperatorArguments(const std::vector<std::shared_ptr<const Operand> >& arguments, const std::string& operatorType, 
                                 const std::vector<std::vector<std::string> >& candidateArguments);
    char const* what() const noexcept override;
private:
    std::vector<std::shared_ptr<const Operand> > arguments;
    std::string operatorType;
    std::vector<std::vector<std::string> > candidateArguments;
    mutable std::string errorMessage;
};

class CustomException : public std::exception {
public:
    CustomException(int column, const std::string& inputExpression);
    const int column;
    const std::string inputExpression;
    mutable std::string errorMessage;
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

class EmptyExpression : std::exception {
public:
    char const* what() const noexcept override;
    mutable std::string errorMessage;
};

#endif
