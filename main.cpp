#include <iostream>
#include <variant>
#include "Lexer.h"
#include "Input.h"
#include "ExpressionTree.h"
#include "Output.h"
#include "DontKnow.h"

int main() {
    try {
    ConsoleInput in;
    std::string input;
    in.getInput(input);
    OperationRegistry operationRegistry;
    initializeOperationMap(operationRegistry);
    ExpressionTree tree(operationRegistry);
    tree.buildExpressionTree(input);
    auto res = tree.evaluate(tree.getHead());
    std::cout << std::endl << "Result :   " ;
    res->print();
    std::cout << std::endl;  
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