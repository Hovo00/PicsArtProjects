#include <iostream>
#include <variant>
#include "Lexer.h"
#include "Input.h"
#include "ExpressionTree.h"
#include "Output.h"

int main() {
    try {
    ConsoleInput in;
    std::string input;
    in.getInput(input);
    Lexer lex;
    auto j = lex.divideTolexems(input);
    ExpressionTree tree;
    tree.buildExpressionTree(j);
    tree.getHead();
    auto res = tree.evaluate(tree.getHead());
    std::cout << std::endl << "Result : " << std::endl;
    res->printValue();  
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
