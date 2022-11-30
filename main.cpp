#include <iostream>
#include <variant>
#include "Lexer.h"
#include "InputClass.h"
#include "ExpressionTree.h"


int main() {
    try {
    ConsoleInput in;
    std::string inputik;
    in.getInput(inputik);
    Lexer lex;
    auto j = lex.divideTolexems(inputik);
    ExpressionTree tree;
    tree.buildExpressionTree(j);
    tree.getHead();
    auto res = tree.evaluate(tree.getHead());
    std::cout << std::endl << "Result : " << std::endl;
    res->printValue();  
    // std::string strik = "1235(";
    // std::cout << TypeInfo::isValidNumber(strik, 0); 
    }
    catch(invalidMatrixOperand& exc) {
        std::cout << exc.what() << exc.col;
    }
    catch(invalidVariable& var) {
        std::cout << var.what() << var.col;
    }
    catch(wrondMatrixDimension& wmd) {
        std::cout << wmd.what() << wmd.curr << " previous defined " << wmd.prev;
    }
}
