#include "InputClass.h"
#include "Token.h"
#include "Matrix.h"
#include "Parser.h"



int main() {

    ConsoleInput in;
    std::string inpStr;
    in.getInput(inpStr);
    Parser pars;
    auto p = pars.do_parse(inpStr);
    //p[4]->doStuff();
}