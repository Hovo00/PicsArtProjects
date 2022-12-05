#include "Lexer.h"

std::vector<std::string > Lexer::divideTolexems(std::string& inpStr) {
    lexems.resize(inpStr.size());
    lexemCount = 0;
    for (int i = 0; i < inpStr.size(); ++i) {
         if (std::isdigit(inpStr[i])) {
            addNumberToLexems(inpStr, i);
         } 
         if (std::isalpha(inpStr[i])) {
            addVariableToLexems(inpStr, i);
         }
         if (inpStr[i] == '{') {
            addMatrixToLexems(inpStr, i);
         }
         if (TypeInfo::isOperator(inpStr[i])) {
            //std::cout << inpStr[i] << std::endl;
            if (inpStr[i] == '-') {
                if ((lexemCount == 0 || lexems[lexemCount - 1][0] == '(') && std::isdigit(inpStr[i+1])) {
                    addNumberToLexems(inpStr, i);
                }
                else if (!TypeInfo::isOperator(lexems[lexemCount - 1][0])){
                    addOperatorToLexems(inpStr, i);
                }
                else {
                    throw invalidSyntax(i, inpStr);
                }
            }
            else {
                addOperatorToLexems(inpStr, i);
            }
         }
    }
    lexems.resize(lexemCount);
    for(auto & i : lexems) {
        std::cout << i << std::endl;
    }
    //return lexems;
    return infixToPostfix(lexems);
}

void Lexer::addNumberToLexems(std::string& inpStr, int& pos) {
    lexems[lexemCount].push_back('n');
    lexems[lexemCount].push_back(inpStr[pos++]);
    while (std::isdigit(inpStr[pos])) {
        lexems[lexemCount].push_back(inpStr[pos++]);
    }
    if (inpStr[pos] == '.') {
        if (pos + 1 == inpStr.size() || inpStr[pos + 1] == ' ') {
            throw invalidSyntax(pos, inpStr);
        }
        lexems[lexemCount].push_back(inpStr[pos++]);
        while(std::isdigit(inpStr[pos])) {
            lexems[lexemCount].push_back(inpStr[pos++]);
        }
    }
    if (std::isalpha(inpStr[pos])) {
        throw invalidVariable(pos, inpStr);
    }
    if (inpStr[pos] == '(' || inpStr[pos] == '{' ||inpStr[pos] == '}') {
        throw invalidSyntax(pos, inpStr);
    }
    ++lexemCount;
}
void Lexer::addVariableToLexems(std::string& inpStr, int& pos) {
    lexems[lexemCount].push_back('v');
    while (std::isalpha(inpStr[pos])) {
        lexems[lexemCount].push_back(inpStr[pos++]);
    }
    if (std::isdigit(inpStr[pos])) {
        throw invalidVariable(pos, inpStr);
    }
    if (inpStr[pos] == '.' || inpStr[pos] == '(') {
        throw invalidSyntax(pos, inpStr);
    }
    ++lexemCount;
}
void Lexer::addMatrixToLexems(std::string& inpStr, int& pos) {
    lexems[lexemCount].push_back('m');
    lexems[lexemCount].push_back(inpStr[pos++]);
    int cCount = 1;
    int metOpenBrCount = 1;
    int metCloseBrCount = 0;
    int dimension = 0;
    int currDimension = 0;
    while (cCount != 0) {
        if(!TypeInfo::isValidMatrixSymbol(inpStr[pos])) {
            throw invalidMatrixOperand(pos, inpStr);
        }
        if (inpStr[pos] == '-') {
            if (!std::isdigit(inpStr[pos + 1])) {
                throw invalidSyntax(pos, inpStr);
            }
            addNumberToMatrix(inpStr, pos);
            if (metOpenBrCount < 3) {
                ++dimension;
            }
            ++currDimension;
        }
        if (std::isdigit(inpStr[pos])) {
            addNumberToMatrix(inpStr, pos);
            if (metOpenBrCount < 3) {
                ++dimension;
            }
            ++currDimension;
        }
        if (inpStr[pos] == '{') {
            ++cCount;
            ++metOpenBrCount;
            if (metOpenBrCount - metOpenBrCount > 2) {
                throw invalidSyntax(pos, inpStr);
            }
        }
        if (inpStr[pos] == '}') {
            --cCount;
            ++metCloseBrCount;
            if (currDimension != dimension && cCount != 0) {
               throw wrondMatrixDimension(pos, dimension, currDimension, inpStr);
            }
            currDimension = 0;
        }
        lexems[lexemCount].push_back(inpStr[pos++]);
    }
    ++lexemCount;
}
void Lexer::addNumberToMatrix(std::string& inpStr, int& pos) {
    lexems[lexemCount].push_back(inpStr[pos++]);
    while (std::isdigit(inpStr[pos])) {
        lexems[lexemCount].push_back(inpStr[pos++]);
    }
    if (inpStr[pos] == '.') {
        if (!std::isdigit(inpStr[pos + 1])) {
            throw invalidSyntax(pos + 1, inpStr);
        }
        lexems[lexemCount].push_back(inpStr[pos++]);
        while (std::isdigit(inpStr[pos])) {
            lexems[lexemCount].push_back(inpStr[pos++]);
        }
        if (inpStr[pos] != ' ' && inpStr[pos] != '}') {
            throw invalidSyntax(pos, inpStr);
        }
    }
    else if (inpStr[pos] != ' ' && inpStr[pos] != '}') {
        throw invalidSyntax(pos, inpStr);
    }
}

void Lexer::addOperatorToLexems(std::string& inpStr, int& pos) {
    //lexems[count].push_back('o');
    lexems[lexemCount].push_back(inpStr[pos]);
    ++lexemCount;
}

std::vector<std::string> Lexer::infixToPostfix(std::vector<std::string>& infix) {
    std::vector<std::string> postfix;
    std::stack<std::string> st;
    for (auto& lexem : infix) {
        if (TypeInfo::isOperator(lexem[0])) {
            if (lexem[0] == '(') {
                st.push(lexem);
                continue;
            }
            if (lexem[0] == ')') {
                while (!st.empty() && st.top() != "(") {
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    st.pop();
                }
                continue;
            }
            if (st.empty()) {
                st.push(lexem);
                continue;
            }
            if (TypeInfo::operPrec(st.top()) < TypeInfo::operPrec(lexem)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && (TypeInfo::operPrec(st.top()) >= TypeInfo::operPrec(lexem))) {
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(lexem);
            }
        }
        else {
            postfix.push_back(lexem);
        }
    }
    while (!st.empty()) {
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}
