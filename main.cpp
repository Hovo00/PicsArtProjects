#include <iostream>
#include <variant>
#include "Lexer.h"
#include "InputClass.h"
#include "ExpressionTree.h"

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
    catch(const invalidMatrixOperand& exc) {
        std::cout << exc.what() << exc.col;
    }
    catch(const invalidVariable& var) {
        std::cout << var.what() << var.col;
    }
    catch(const wrondMatrixDimension& wmd) {
        std::cout << wmd.what() << wmd.curr << " previous defined " << wmd.prev;
    }
    catch(const invalidSyntax& is) {
        std::cout << is.what() << is.col;
    }
    catch(const UnsupportedOperatorArguments& excep) {
        std::cout << excep.what();
    }
}
