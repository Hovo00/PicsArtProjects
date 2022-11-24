#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Lexer.h"
#include "matrixAdd.h"
#include "matrixSub.h"
#include "matrixMul.h"

class Parser {
public:
    std::vector<std::shared_ptr<Token> >& do_parse(std::string&);
    void addToken(std::string&, std::vector<std::shared_ptr<Token> >&);
private:
    Lexer lexer;
    std::vector<std::shared_ptr<Token>> tokens;
};

#endif
