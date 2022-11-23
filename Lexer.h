#ifndef LEXER_H
#define LEXER_H

//CLEAN UP HERE ***

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "TypeInfo.h"

class Lexer {
public:
    std::vector<std::string> divideTolexems(std::string&);
private:
    //int prec(std::string);
    std::vector<std::string> infixToPostfix(std::vector<std::string>&);
};

#endif