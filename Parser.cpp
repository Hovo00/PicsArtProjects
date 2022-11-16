#include "Parser.h"


Parser::~Parser() {
    for (auto & p : tokens) {
        delete p;
    }
}

std::vector<Token*>& Parser::do_parse(std::string& inpStr) {
    auto lexems = lexer.divideTolexems(inpStr);
    for (auto& v : lexems) {
        std::cout << v << std::endl;
    }
    for (auto& lexem : lexems) {
        addToken(lexem, tokens);
    }
    return tokens;
}
void Parser::addToken(std::string& lexem, std::vector<Token*>& tokens) {
    switch(lexem[0]) {
    case 'm' : tokens.push_back(new Matrix(lexem)); break;
    case '+' : tokens.push_back(new matrixAdd()); break;
    case '-' : tokens.push_back(new matrixSub()); break;
    case '/' : tokens.push_back(new matrixDiv()); break;
    case '*' : tokens.push_back(new matrixMul()); break;
    case 'v' : tokens.push_back(new Matrix()); break;
    }
}
