#include "Lexer.h"

Lexer::VectorOfLexems Lexer::divideTolexems(const std::string& inpStr) {
    lexems.clear();
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

void Lexer::addNumberToLexems(const std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "float";
    lexems[lexemIndex].second.push_back(inpStr[pos++]);
    while (pos < inpStr.size() && std::isdigit(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (inpStr[pos] == '.') {
        if (pos + 1 == inpStr.size() || inpStr[pos + 1] == ' ') {
            throw invalidSyntax(pos, inpStr);
        }
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
        while(pos < inpStr.size() && std::isdigit(inpStr[pos])) {
            lexems[lexemIndex].second.push_back(inpStr[pos++]);
        }
    }
    if (std::isalpha(inpStr[pos])) {
        throw invalidVariable(pos, inpStr);
    }
    if (inpStr[pos] == '(' || inpStr[pos] == '{' ||inpStr[pos] == '}') {
        throw invalidSyntax(pos, inpStr);
    }
}
void Lexer::addVariableToLexems(const std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "var";
    while (pos < inpStr.size() && std::isalpha(inpStr[pos])) {
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
void Lexer::addMatrixToLexems(const std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "matrix";
    lexems[lexemIndex].second.push_back(inpStr[pos++]);
    int closingBrecketsExpected = 1;
    int openingBrecketsCount = 1;
    int closingBrecketsCount = 0;
    int dimension = 0;
    int currentRawElementsCount = 0;
    while (pos < inpStr.size() && closingBrecketsExpected != 0) {
        if(!TypeInfo::isValidMatrixSymbol(inpStr[pos])) {
            throw invalidMatrixOperand(pos, inpStr);
        }
        if (inpStr[pos] == '-') {
            if (!std::isdigit(inpStr[pos + 1])) {
                throw invalidSyntax(pos, inpStr);
            }
            addNumberToMatrix(inpStr, pos, lexemIndex);
            if (openingBrecketsCount < 3) {
                ++dimension;
            }
            ++currentRawElementsCount;
        }
        else if (std::isdigit(inpStr[pos])) {
            addNumberToMatrix(inpStr, pos, lexemIndex);
            // if openingBrecketsCount < 3 it means that will still count elements of first row
            if (openingBrecketsCount < 3) {
                ++dimension;
            }
            ++currentRawElementsCount;
        }
        if (inpStr[pos] == '{') {
            ++closingBrecketsExpected;
            ++openingBrecketsCount;
            if (openingBrecketsCount - closingBrecketsCount > 2) {
                throw invalidSyntax(pos, inpStr);
            }
        }
        if (inpStr[pos] == '}') {
            --closingBrecketsExpected;
            ++closingBrecketsCount;
            if (currentRawElementsCount != dimension && closingBrecketsExpected != 0) {
               throw wrondMatrixDimension(pos, dimension, currentRawElementsCount, inpStr);
            }
            currentRawElementsCount = 0;
        }
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    }
}
void Lexer::addNumberToMatrix(const std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    while (pos < inpStr.size() && std::isdigit(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
    }
    if (inpStr[pos] == '.') {
        if (!std::isdigit(inpStr[pos + 1])) {
            throw invalidSyntax(pos + 1, inpStr);
        }
        lexems[lexemIndex].second.push_back(inpStr[pos++]);;
        while (pos < inpStr.size() && std::isdigit(inpStr[pos])) {
            lexems[lexemIndex].second.push_back(inpStr[pos++]);;
        }
    }
    if (inpStr[pos] != ' ' && inpStr[pos] != '}') {
        throw invalidSyntax(pos, inpStr);
    }
}

void Lexer::addOperatorToLexems(const std::string& inpStr, int& pos, int lexemIndex) {
    lexems[lexemIndex].first = "oper";
    lexems[lexemIndex].second.push_back(inpStr[pos]);
}

Lexer::VectorOfLexems Lexer::infixToPostfix(const Lexer::VectorOfLexems& infix) {
    // for(auto & i : infix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    Lexer::VectorOfLexems postfix;
    std::stack<std::pair<std::string, std::string> > st;
    for (auto& lexem : infix) {
        if (lexem.first == "oper") {
            if (lexem.second == "(") {
                st.push(lexem);
            }
            else if (lexem.second == ")") {
                while (!st.empty() && st.top().second != "(") {
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    st.pop();
                }
            }
            else if (st.empty()) {
                st.push(lexem);
            }
            else if (TypeInfo::precedence(st.top().second) < TypeInfo::precedence(lexem.second)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && (TypeInfo::precedence(st.top().second) >= TypeInfo::precedence(lexem.second))) {
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

void Lexer::addFunctionToLexems(const std::string& inpStr, int& pos, int& lexemCount) {
    if (inpStr[pos++] != '(') {
        throw invalidSyntax(pos, inpStr);
    }
    lexems[lexemCount].first = "oper";
    int argCount = TypeInfo::argumentCount(lexems[lexemCount].second);
    int commasCount = 0;
    while (inpStr[pos] != ')' && pos < inpStr.size()) {
        while(inpStr[pos] == ' ' && pos < inpStr.size()) {
            ++pos;
        }
        if (std::isdigit(inpStr[pos])) {
            addNumberToLexems(inpStr, pos, lexemCount + 1);
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
        else if (inpStr[pos] == ',') {
            if (++commasCount == argCount) {
            //change exception
            throw invalidSyntax(pos, inpStr);
        }
        ++pos;
        }
    //++pos;
    }
    if (argCount - commasCount != 1) {
        throw invalidSyntax(pos, inpStr);
    }
}
