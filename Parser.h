#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <iostream>
#include <memory>
#include "Token.h"
#include "Lexer.h"
#include "Operator.h"

class Parser {
public:
    std::vector<std::shared_ptr<Token> >& do_parse(std::string&);
    void addToken(std::string&, std::vector<std::shared_ptr<Token> >&);
    //~Parser();
    int prec(std::string);
private:
    Lexer lexer;
    std::vector<std::shared_ptr<Token>> tokens;
};

#endif
