#ifndef EXCEPTIONXX_Haaaaaa
#define EXCEPTIONXX_Haaaaaa

#include <iostream>
#include <exception>

class invalidMatrixOperand : public std::exception {
public:
    invalidMatrixOperand(int cl) {
        col = cl;
    }
    char const* what() const noexcept override {
        
        return "Invalid symbol in matrix brackets in col : ";
    }
    int col;
};
class invalidVariable : public std::exception {
public:
    invalidVariable(int cl) {
        col = cl;
    }
    char const* what() const noexcept override {
        
        return " Invalid Variable (ambiguity number or variable ) in col : ";
    }
    int col;
};

class wrondMatrixDimension : public std::exception {
public:
    wrondMatrixDimension(int prv, int crr) {
        prev = prv;
        curr = crr;
    }
    char const* what() const noexcept override {
        
        return " Invalid column count : ";
    }
    int prev;
    int curr;
};

#endif
