#include "InputClass.h"
#include "Token.h"
#include "Matrix.h"
#include "Parser.h"
#include "Tree.h"



int main() {
    ConsoleInput in;
    std::string inpStr;
    in.getInput(inpStr);
    Parser pars;
    auto parsed = pars.do_parse(inpStr);
    Tree tree;
    tree.BuildTree(parsed);
    auto j = tree.evaluate(tree.getHead());
    j->printOperand();
}