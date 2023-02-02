#include "Input.hpp"
#include "Output.hpp"
#include "MapInitialization.hpp"


int main(int argc, char *argv[]) {
    try {
    std::string inputExpression;
    bool mode = true;
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
    //inputExpression = "{{2 2} {2 2}} + 4 * {{2 33.3} {2 3}} + det({{2 12} {122 7}})";
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
    catch(const std::string& excep) {
        ConsoleOutput::printErrorMessage(excep);
    }
}
