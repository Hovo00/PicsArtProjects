#ifndef EXCEPTIONXX_H
#define EXCEPTIONXX_H

#include <iostream>
#include <exception>
#include <string>

class UnsupportedOperatorArguments : public std::exception {
public:
    UnsupportedOperatorArguments(const std::string& message);
    char const* what() const noexcept override;
private:
    std::string errorMessage;
};

class customException : public std::exception {
public:
    customException(int column, std::string inputExpression);
    const int column;
    const std::string inputExpression;
};

class invalidMatrixOperand : public customException {
public:
    invalidMatrixOperand(int column, std::string inputExpression);
    char const* what() const noexcept override;
};
class invalidVariable : public customException {
public:
    invalidVariable(int cl, std::string inputExpression);
    char const* what() const noexcept override;
};
class invalidSyntax : public customException {
public:
    invalidSyntax(int cl, std::string inputExpression);
    char const* what() const noexcept override;
};

class wrondMatrixDimension : public customException {
public:
    wrondMatrixDimension(int column, int previous, int current, std::string inputExpression);
    char const* what() const noexcept override;
    const int previous;
    const int current;
};

#endif
