#ifndef EXCEPTIONXX_Haaaaaa
#define EXCEPTIONXX_Haaaaaa

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
    int col;
    std::string inpStr;
    void showErrorPlace() const;
};

class invalidMatrixOperand : public customException {
public:
    invalidMatrixOperand(int cl, std::string inpSt);
    char const* what() const noexcept override;
};
class invalidVariable : public customException {
public:
    invalidVariable(int cl, std::string inpSt);
    char const* what() const noexcept override;
};
class invalidSyntax : public customException {
public:
    invalidSyntax(int cl, std::string inpSt);
    char const* what() const noexcept override;
};

class wrondMatrixDimension : public customException {
public:
    wrondMatrixDimension(int pos, int prv, int crr, std::string inpSt);
    char const* what() const noexcept override;
    int prev;
    int curr;
};

#endif
