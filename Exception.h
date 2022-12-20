#ifndef EXCEPTIONXX_H
#define EXCEPTIONXX_H

#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include "Operand.h"

class UnsupportedOperatorArguments : public std::exception {
public:
    UnsupportedOperatorArguments(const std::vector<std::shared_ptr<Operand> >& arguments, const std::string& operatorType);
    char const* what() const noexcept override;
private:
    std::vector<std::shared_ptr<Operand> > arguments;
    std::string operatorType;
};

class customException : public std::exception {
public:
    customException(int column, const std::string& inputExpression);
    const int column;
    const std::string inputExpression;
};

class invalidMatrixOperand : public customException {
public:
    invalidMatrixOperand(int column, const std::string& inputExpression);
    char const* what() const noexcept override;
};
class invalidVariable : public customException {
public:
    invalidVariable(int cl, const std::string& inputExpression);
    char const* what() const noexcept override;
};
class invalidSyntax : public customException {
public:
    invalidSyntax(int cl, const std::string& inputExpression);
    char const* what() const noexcept override;
};

class wrondMatrixDimension : public customException {
public:
    wrondMatrixDimension(int column, int previous, int current, const std::string& inputExpression);
    char const* what() const noexcept override;
    const int previous;
    const int current;
};

#endif
