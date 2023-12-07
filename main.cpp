#include "Evaluator.hpp"
#include "Input.hpp"
#include "MapInitialization.hpp"
#include "OperandValidators.hpp"
#include "CreatorFunctions.hpp"


int main(int argc, char *argv[]) {
    try {
        std::string inputExpression;
        bool loopInputMode = false;
        if (argc > 2 && std::string(argv[1]) == "-l") {
            inputExpression = argv[2];
            loopInputMode = true;
        }
        else {
            inputExpression = argv[1];
        }
        Evaluator evaluator;
        initEvaluatorOperationMap(evaluator);
        evaluator.addOperand("float", Validators::validateFloat, Creators::createFloat);
        evaluator.addOperand("matrix", Validators::validateMatrix, Creators::createMatrix);
        ConsoleInput::getInput(evaluator, loopInputMode, inputExpression);
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
        ConsoleOutput::printErrorMessageRed(std::string(excep.what()));
    }
    catch(const EmptyExpression& excep) {
        ConsoleOutput::printErrorMessageRedWhite(std::string(excep.what()));
    }
    catch(const std::string& excep) {
        ConsoleOutput::printErrorMessageRedWhite(excep);
    }
}
