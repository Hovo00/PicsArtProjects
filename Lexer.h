#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stack>
#include "Exception.h"

#include "TypeInfo.h"

class Lexer {
public:
    std::vector<std::string> divideTolexems(std::string&);
private:
    std::vector<std::string> infixToPostfix(std::vector<std::string>&);
};

#endif