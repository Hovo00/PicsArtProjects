#ifndef OUTPUTClASS_H
#define OUTPUTClASS_H
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

constexpr const char * RED = "\e[0;31m";
constexpr const char * GREEN = "\e[0;32m";
constexpr const char * NOCOLOR = "\e[0m";
constexpr const char * REDWHITE = "\e[41m";

class OutputBase {
public:

};

class ConsoleOutput : public OutputBase {
public:
    static void showErrorPlace(const std::string& errorMessage, const std::string& inputExpression, int pos);
    static void printErrorMessage(const std::string& errorMessage);
};

#endif
