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
    //std::cout << (2 == 4 ? 12 : 3)<< std::endl;
    //inputExpression = "4 ? 2 : 2";
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
