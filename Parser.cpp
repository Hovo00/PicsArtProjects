#include "Parser.h"

std::vector<std::shared_ptr<Token> >& Parser::do_parse(std::string& inpStr) {
    auto lexems = lexer.divideTolexems(inpStr);
    for (auto& v : lexems) {
        std::cout << v << std::endl;
    }
    for (auto& lexem : lexems) {
        addToken(lexem, tokens);
    }
    return tokens;
}
void Parser::addToken(std::string& lexem, std::vector<std::shared_ptr<Token> >& tokens) {
    switch(lexem[0]) {
    case 'm' : tokens.push_back(std::make_shared<Matrix>(lexem)); break;
    case '+' : tokens.push_back(std::make_shared<matrixAdd>()); break;
    case '-' : tokens.push_back(std::make_shared<matrixSub>()); break;
    case '*' : tokens.push_back(std::make_shared<matrixMul>()); break;
    case 'v' : tokens.push_back(std::make_shared<Matrix>()); break;
    }
}
