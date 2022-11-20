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
    j.printMat();
    // auto p = pars.do_parse(inpStr);
    // tree.BuildTree(p);
    // auto head = tree.getHead();
    // tree.inOrder(head);
    // matrixSub mul;
    // auto res = mul.doStuff(std::vector<Matrix>{Matrix("{{1 2 } {3 4}}"), Matrix("{{2 3} {2 2}}")});
    // res.printMat();

    
}