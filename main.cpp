#include <fstream>
#include "Exception.hpp"
#include "Input.hpp"
#include "Evaluator.hpp"
#include "Output.hpp"
#include "MapInitialization.hpp"


int main(int argc, char *argv[]) {
    try {
    std::string inputExpression;
    bool mode = true;
    std::cout << argc << std::endl;
    if (argc == 1) {
        inputExpression = " ";
    }
    else if (std::string(argv[1]) == "-s") {
        mode = false;
        inputExpression = argv[2];
    }
    else {
        inputExpression = argv[1];
    }
    //inputExpression = "1 + 2";
    Evaluator evaluator;
    initEvaluatorOperationMap(evaluator);
    auto result = evaluator.evaluate(inputExpression);
    ConsoleInput input;
    std::cout << std::endl << "Result :  ";
    std::cout << result->toString();
    std::cout << std::endl;
    while (mode) {
        std::string inputExpression;
        input.getInput(inputExpression);
        if (inputExpression == "quit") {
            break;
        }
        auto result = evaluator.evaluate(inputExpression);
        std::cout << std::endl << "Result :  ";
        std::cout << result->toString();
        std::cout << std::endl;
    }
}
    catch(const InvalidMatrixOperand& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const InvalidVariable& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const WrondMatrixDimension& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const invalidSyntax& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const UnsupportedOperatorArguments& excep) {
        ConsoleOutput::printErrorMessage(std::string(excep.what()));
    }
    catch(const EmptyExpression& excep) {
        ConsoleOutput::printErrorMessage(std::string(excep.what()));

    }
}

// ({{2 2} {2 2}} == {{2 2} {2 2}}) ? 4 : 5
//({{2 2} {2 2}} == {{1 1} {1 1}} * 2) ? 17 : 2
// -{{2 2} {2 2}}
// -({{2 2} {2 2}} + 4 * {{2 33.3} {2 3}} + det(a))
// {{3242 2344} {2334.c 2344}}
// {{23.234 32.4} {234.4. 323}}
// {{232 23} {232 22 } {    324  34  44}}
//( ( ( inverse(32323) )))
//det(a) * transpose(c)
//{{23 32} {24 224}}
//{{32 2324} {2344 2}}
//124 * (sin(30) + -3 * 4-222 * 6) / 12
//select({{2 2} {2 2}}, {{ 22 2} {2 2}}, {{2332 3 } {22 22}})
//select({{2 2} {2 2}}, {{ 22 2} {2 2}}, {{2332 3 } {22 22}} , {{2 2} {2 2}})
//(a == b) * 4
