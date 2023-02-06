#ifndef INPUTClASS_H
#define INPUTClASS_H
#include <iostream>
#include <string>
#include "Output.hpp"
#include "Evaluator.hpp"

// class InputBase {
// public:
//     virtual void getInput(std::string& inpStr) = 0;
// };


class ConsoleInput {
public:
    static void getInput(Evaluator& evaluator, bool loopInputMode, std::string inputExpression);
private:
    static void _getInput(std::string& inpStr);
};

#endif
