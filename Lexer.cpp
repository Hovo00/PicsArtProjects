#include "Lexer.h"

Lexer::VectorOfLexems Lexer::divideTolexems(std::string& inpStr) {
    lexems.resize(inpStr.size());
    int lexemCount = 0;
    for (int i = 0; i < inpStr.size(); ++i) {
        if (std::isdigit(inpStr[i])) {
            addNumberToLexems(inpStr, i, lexemCount);
            ++lexemCount;
        } 
        else if (std::isalpha(inpStr[i])) {
            addVariableToLexems(inpStr, i, lexemCount);
            if (TypeInfo::isReserved(lexems[lexemCount].second)) {
                //std::cout << i << " " << lexemCount << std::endl;
                addFunctionToLexems(inpStr, i, lexemCount);
            }
            ++lexemCount;
        }
        else if (inpStr[i] == '{') {
            addMatrixToLexems(inpStr, i, lexemCount);
            ++lexemCount;
        }
        if (TypeInfo::isOperator(inpStr, i)) {
            if (inpStr[i] == '(') {
            }

            if (inpStr[i] == '-') {
                if ((lexemCount == 0 || lexems[lexemCount - 1].second == "(") && std::isdigit(inpStr[i+1])) {
                    addNumberToLexems(inpStr, i, lexemCount);
                }
                else if (lexems[lexemCount - 1].first != "oper" || lexems[lexemCount - 1].second == ")"){
                    addOperatorToLexems(inpStr, i, lexemCount);
                }
                else {
                    throw invalidSyntax(i, inpStr);
                }
            }
            else {
                addOperatorToLexems(inpStr, i, lexemCount);
            }
            ++lexemCount;
        }
    }
    lexems.resize(lexemCount);
    initializeVariables();
    return infixToPostfix(lexems);
}

void Lexer::addNumberToLexems(std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "float";
    lexems[lexemIndex].second.push_back(inpStr[pos++]);
    while (std::isdigit(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (inpStr[pos] == '.') {
        if (pos + 1 == inpStr.size() || inpStr[pos + 1] == ' ') {
            throw invalidSyntax(pos, inpStr);
        }
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
        while(std::isdigit(inpStr[pos])) {
            lexems[lexemIndex].second.push_back(inpStr[pos++]);
        }
    }
    if (std::isalpha(inpStr[pos])) {
        //std::cout << pos << std::endl;
        throw invalidVariable(pos, inpStr);
    }
    if (inpStr[pos] == '(' || inpStr[pos] == '{' ||inpStr[pos] == '}') {
        throw invalidSyntax(pos, inpStr);
    }
    //std::cout << "firstTime" << std::endl;
}
void Lexer::addVariableToLexems(std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "var";
    while (std::isalpha(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (std::isdigit(inpStr[pos]) && !TypeInfo::isReserved(lexems[lexemIndex].second)) {
        throw invalidVariable(pos, inpStr);
    }
   // std::cout << lexems[lexemIndex].second << std::endl;
    if (inpStr[pos] == '.' || inpStr[pos] == '{') {
        throw invalidSyntax(pos, inpStr);
    }
}
void Lexer::addMatrixToLexems(std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "matrix";
    lexems[lexemIndex].second.push_back(inpStr[pos++]);
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
            addNumberToMatrix(inpStr, pos, lexemIndex);
            if (metOpenBrCount < 3) {
                ++dimension;
            }
            ++currDimension;
        }
        if (std::isdigit(inpStr[pos])) {
            addNumberToMatrix(inpStr, pos, lexemIndex);
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
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    }
}
void Lexer::addNumberToMatrix(std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    while (std::isdigit(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    }
    if (inpStr[pos] == '.') {
        if (!std::isdigit(inpStr[pos + 1])) {
            throw invalidSyntax(pos + 1, inpStr);
        }
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
        while (std::isdigit(inpStr[pos])) {
            lexems[lexemIndex].second.push_back(inpStr[pos++]);;
        }
        if (inpStr[pos] != ' ' && inpStr[pos] != '}') {
            throw invalidSyntax(pos, inpStr);
        }
    }
    else if (inpStr[pos] != ' ' && inpStr[pos] != '}') {
        throw invalidSyntax(pos, inpStr);
    }
}

void Lexer::addOperatorToLexems(std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "oper";
    lexems[lexemIndex].second.push_back(inpStr[pos]);
}

Lexer::VectorOfLexems Lexer::infixToPostfix(Lexer::VectorOfLexems& infix) {
    // for(auto & i : infix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    Lexer::VectorOfLexems postfix;
    std::stack<std::pair<std::string, std::string> > st;
    for (auto& lexem : infix) {
        if (lexem.first == "oper") {
            if (lexem.second == "(") {
                st.push(lexem);
                //continue;
            }
            else if (lexem.second == ")") {
                while (!st.empty() && st.top().second != "(") {
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    st.pop();
                }
                //continue;
            }
            else if (st.empty()) {
                st.push(lexem);
                //continue;
            }
            else if (TypeInfo::operPrec(st.top().second) < TypeInfo::operPrec(lexem.second)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && (TypeInfo::operPrec(st.top().second) >= TypeInfo::operPrec(lexem.second))) {
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
    // for(auto & i : postfix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    return postfix;
}

void Lexer::initializeVariables() {
    std::unordered_map<std::string, int> knownVariables;
    for (int i = 0; i < lexems.size(); ++i) {
        if (lexems[i].first == "var") {
            if (knownVariables.find(lexems[i].second) != knownVariables.end()) {
                int j = knownVariables[lexems[i].second];
                lexems[i].first = lexems[j].first;
                lexems[i].second = lexems[j].second;
                continue;
            }
            knownVariables[lexems[i].second] = i;
            inputVariable(i);
        }
    }
}

void Lexer::inputVariable(int lexemIndex) {
    std::string userInput;
    std::cout << "Enter variable " << lexems[lexemIndex].second << " ";
    std::getline(std::cin, userInput);
    int i = 0;
    lexems[lexemIndex].second = "";
    if (std::isdigit(userInput[i])) {
        addNumberToLexems(userInput, i, lexemIndex);
    }
    else if (userInput[0] == '{') {
        addMatrixToLexems(userInput, i, lexemIndex);
    }
    else throw invalidSyntax(i, userInput);
}

void Lexer::addFunctionToLexems(std::string& inpStr, int& pos, int& lexemCount) {
    if (inpStr[pos++] != '(') {
        throw invalidSyntax(pos, inpStr);
    }
    lexems[lexemCount].first = "oper";
    int argCount = TypeInfo::argCount[lexems[lexemCount].second];
    int count = 0;
    while (inpStr[pos] != ')' && pos < inpStr.size()) {
        if (count > argCount) {
            //change exception
            std::cout << "nooooo" << std::endl;
            throw invalidSyntax(pos, inpStr);
        }
        if (std::isdigit(inpStr[pos])) {
            addNumberToLexems(inpStr, pos, lexemCount + 1);
            std::cout << pos << std::endl;
            ++lexemCount;
        }
        else if (inpStr[pos] == '{') {
            addMatrixToLexems(inpStr, pos, lexemCount + 1);
            ++lexemCount;
        }
        else if (std::isalpha(inpStr[pos])) {
            addVariableToLexems(inpStr, pos, lexemCount + 1);
            ++lexemCount;
        }
        //++pos;
        ++count;
    }
    ++pos;
}
