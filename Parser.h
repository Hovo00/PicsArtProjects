#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Operator.h"

class Parser {
public:
    std::vector<Token*>& do_parse(std::string&);
    void addToken(std::string&, std::vector<Token*>&);
    ~Parser();
    int prec(std::string);
private:
    Lexer lexer;
    std::vector<Token*> tokens;
};

#endif
