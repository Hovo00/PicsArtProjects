#include <iostream>
#include <variant>
#include "Lexer.h"
#include "Input.h"
#include "ExpressionTree.h"
#include "Output.h"


// test for addOperatorOverload function
std::shared_ptr<Operand> matrixFloatMultiplication(std::vector<std::shared_ptr<Operand> > arguments) {
    auto matrix = std::static_pointer_cast<Matrix>(arguments[0]);
    auto flt = std::static_pointer_cast<Float>(arguments[1]);
    int rows = matrix->getRowCount();
    int cols = matrix->getColCount();
    auto result = std::make_shared<Matrix>(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->at(i, j) = matrix->at(i, j) * flt->getValue();
        }
    }
    return result;
}

int main() {
    try {
    ConsoleInput in;
    std::string input;
    OperationRegistry::addOperatorOverload("*", matrixFloatMultiplication, "*matrixfloat");
    in.getInput(input);
    auto j = Lexer::divideTolexems(input);
    ExpressionTree tree;
    tree.buildExpressionTree(j);
    tree.getHead();
    auto res = tree.evaluate(tree.getHead());
    std::cout << std::endl << "Result : " << std::endl;
    res->print();  
    }
    catch(const invalidMatrixOperand& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const invalidVariable& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const wrondMatrixDimension& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const invalidSyntax& excep) {
        ConsoleOutput::showErrorPlace(std::string(excep.what()), excep.inputExpression, excep.column);
    }
    catch(const UnsupportedOperatorArguments& excep) {
        ConsoleOutput::printErrorMessage(std::string(excep.what()));
    }
}
