#include "Lexer.hpp"

Lexer::Lexer(const OperationRegistry& registry) : _operationRegistry(registry){

}

Lexer::VectorOfLexems Lexer::divideTolexems(const std::string& inpStr) const{
    Lexer::VectorOfLexems lexems;
    lexems.resize(inpStr.size() * 2);
    int lexemCount = 0;
    int i = 0;
    while (i < inpStr.size()) {
        if (std::isdigit(inpStr[i])) {
            addNumberToLexems(inpStr, lexems, i, lexemCount);
        }
        else if (std::isalpha(inpStr[i])) {
            addVariableToLexems(inpStr, lexems, i, lexemCount);
        }
        else if (inpStr[i] == '{') {
            addMatrixToLexems(inpStr, lexems, i, lexemCount);
        }
        else if (_operationRegistry.isOperatorSymbol(inpStr[i])) {
            addOperatorToLexems(inpStr, lexems, i, lexemCount);
        }
        else if (inpStr[i] == '(' || inpStr[i] == ')') {
            addBracketToLexems(inpStr[i], lexems, i, lexemCount);
            ++lexemCount;
        }
        else if (inpStr[i] == ' ') {
            ++i;
        }
        else {
            throw invalidSyntax(i, inpStr);
        }
    }
    lexems.resize(lexemCount);
    initializeVariables(lexems);
    return infixToPostfix(lexems);
}

void Lexer::addNumberToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex) const{
    lexems[lexemIndex].first = "float";
    lexems[lexemIndex].second = cutNumberFromExpression(inpStr, pos);
    ++lexemIndex;
    if (pos == inpStr.size()) {
        return;
    }
    if (!_operationRegistry.isOperatorSymbol(inpStr[pos]) && inpStr[pos] != ')' && inpStr[pos] != ' ' && inpStr[pos] != ',') {
        throw invalidSyntax(pos, inpStr);
    }
}
void Lexer::addVariableToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex) const{
    lexems[lexemIndex].first = "var";
    while (pos < inpStr.size() && std::isalpha(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (_operationRegistry.isFunction(lexems[lexemIndex].second)) {
        addFunctionToLexems(inpStr, lexems, pos, lexemIndex);
        return;
    }
    if (pos == inpStr.size()) {
        ++lexemIndex;
        return;
    }
    //here error
    if (inpStr[pos] != ' ' && !_operationRegistry.isOperatorSymbol(inpStr[pos]) && inpStr[pos] != ')' && inpStr[pos] != ',') {
        if (!_operationRegistry.isFunction(lexems[lexemIndex].second)) {
            throw InvalidVariable(pos, inpStr);
        }
    }
    ++lexemIndex;
}

void Lexer::addMatrixToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex) const{
    lexems[lexemIndex].first = "matrix";
    if (inpStr[pos] == '-') {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    lexems[lexemIndex].second.push_back(inpStr[pos++]);
    int closingBrecketsExpected = 1;
    int openingBrecketsCount = 1;
    int closingBrecketsCount = 0;
    int dimension = 0;
    int currentRawElementsCount = 0;
    while (pos < inpStr.size() && closingBrecketsExpected != 0) {
        if(!isValidMatrixSymbol(inpStr[pos])) {
            throw InvalidMatrixOperand(pos, inpStr);
        }
        if (inpStr[pos] == '-' || std::isdigit(inpStr[pos])) {
            lexems[lexemIndex].second += cutNumberFromExpression(inpStr, pos);
            if (pos == inpStr.size()) {
                throw invalidSyntax(pos, inpStr);
            }
            if (inpStr[pos] != '}' && inpStr[pos] != ' ') {
                throw invalidSyntax(pos, inpStr);
            }
            if (openingBrecketsCount < 3) {
                ++dimension;
            }
            ++currentRawElementsCount;
        }
        else if (inpStr[pos] == '{') {
            ++closingBrecketsExpected;
            ++openingBrecketsCount;
            if (openingBrecketsCount - closingBrecketsCount > 2) {
                throw invalidSyntax(pos, inpStr);
            }
            lexems[lexemIndex].second.push_back(inpStr[pos++]);
        }
        else if (inpStr[pos] == '}') {
            --closingBrecketsExpected;
            ++closingBrecketsCount;
            if (currentRawElementsCount != dimension && closingBrecketsExpected != 0) {
               throw WrondMatrixDimension(pos, dimension, currentRawElementsCount, inpStr);
            }
            currentRawElementsCount = 0;
            lexems[lexemIndex].second.push_back(inpStr[pos++]);
        }
        else if (inpStr[pos] == ' ') {
            lexems[lexemIndex].second.push_back(inpStr[pos++]);
        }
    }
    ++lexemIndex;
}

void Lexer::addOperatorToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex) const{
    std::string Operator;
    while (pos < inpStr.size() && _operationRegistry.isOperatorSymbol(inpStr[pos])) {
        Operator.push_back(inpStr[pos++]);
    }
    if (!_operationRegistry.isOperator(Operator) || (pos == inpStr.size() &&
        _operationRegistry.operationInfo(Operator).notation != Notation::Postfix)) {
        throw invalidSyntax(pos, inpStr);
    }
    if (Operator == "-") {
        // check does it something like , -4 or 5 + -4 (allowed cases)
        if (lexemIndex == 0 || lexemIndex > 0 && (lexems[lexemIndex - 1].first == "oper" || lexems[lexemIndex - 1].second == "(")) {
            addNegativeLexem(inpStr, lexems, pos, lexemIndex);
            return;
        }
    }
    // such cases as,  * 5 or 4 + * 5 are not allowed
    else if (lexemIndex == 0 || lexemIndex > 0 && lexems[lexemIndex - 1].first == "oper") {
        if (!_operationRegistry.isFunction(lexems[lexemIndex - 1].second)) {
            throw invalidSyntax(pos - 1, inpStr);
        }
    }

    //oterwise its normal case , as 4 * 5 or 4 - 5
    lexems[lexemIndex].first = "oper";
    lexems[lexemIndex].second = Operator;
    ++lexemIndex;
}

Lexer::VectorOfLexems Lexer::infixToPostfix(const Lexer::VectorOfLexems& infix) const{
    // for(auto & i : infix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    Lexer::VectorOfLexems postfix;
    std::stack<std::pair<std::string, std::string> > st;
    for (const auto& lexem : infix) {
        if (lexem.first == "oper") {
            if (lexem.second == "?") {
                if (st.empty()) {
                    postfix.push_back(lexem);
                }
            }
            else if (st.empty()) {
                st.push(lexem);
            }
            else if (st.top().first != "oper" ||
                    _operationRegistry.operationInfo(st.top().second).precedence < _operationRegistry.operationInfo(lexem.second).precedence) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && st.top().first == "oper" &&
                      (_operationRegistry.operationInfo(st.top().second).precedence >= _operationRegistry.operationInfo(lexem.second).precedence)) {

                    if ((_operationRegistry.operationInfo(st.top().second).precedence == _operationRegistry.operationInfo(lexem.second).precedence) &&
                         _operationRegistry.operationInfo(st.top().second).associativity == Associativity::RightToLeft) {
                        break;
                    }
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(lexem);
            }
        }
        else if (lexem.second == "(") {
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
        else {
            postfix.push_back(lexem);
        }
    }
    while (!st.empty()) {
        postfix.push_back(st.top());
        st.pop();
    }
    for(auto & i : postfix) {
    }
    return postfix;
}

void Lexer::initializeVariables(Lexer::VectorOfLexems& lexems) const{
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
            inputVariable(lexems, i);
        }
    }
}

void Lexer::inputVariable(Lexer::VectorOfLexems& lexems, int lexemIndex) const{
    std::string userInput;
    std::cout << "Enter variable " << lexems[lexemIndex].second << " ";
    std::getline(std::cin, userInput);
    int i = 0;
    lexems[lexemIndex].second = "";
    if (std::isdigit(userInput[i])) {
        addNumberToLexems(userInput, lexems, i, lexemIndex);
    }
    else if (userInput[0] == '{') {
        addMatrixToLexems(userInput, lexems, i, lexemIndex);
    }
    else {
        throw invalidSyntax(i, userInput);
    }
}

void Lexer::addFunctionToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemCount) const{
    if (inpStr[pos++] != '(') {
        throw invalidSyntax(pos, inpStr);
    }
    lexems[lexemCount].first = "oper";
    int argCount = _operationRegistry.operationInfo(lexems[lexemCount++].second).argumentCount;
    int commasCount = 0;
    while (inpStr[pos] != ')' && pos < inpStr.size()) {
        if (std::isdigit(inpStr[pos])) {
            addNumberToLexems(inpStr, lexems, pos, lexemCount);
        }
        else if (inpStr[pos] == '{') {
            addMatrixToLexems(inpStr, lexems, pos, lexemCount);
        }
        else if (std::isalpha(inpStr[pos])) {
            addVariableToLexems(inpStr, lexems, pos, lexemCount);
        }
        else if (_operationRegistry.isOperatorSymbol(inpStr[pos])) {
            addOperatorToLexems(inpStr, lexems, pos, lexemCount);
        }
        else if (inpStr[pos] == ',') {
            if (++commasCount == argCount) {
            //change exception
            throw invalidSyntax(pos, inpStr);
        }
        ++pos;
        }
        else if (inpStr[pos] == ' ') {
            ++pos;
        }
        else {
            throw invalidSyntax(pos, inpStr);
        }
    }
    if (argCount - commasCount != 1) {
        throw invalidSyntax(pos, inpStr);
    }
    if (inpStr[pos] != ')') {
        throw invalidSyntax(pos, inpStr);
    }
    ++pos;
}
std::string Lexer::cutNumberFromExpression(const std::string& inpStr, int& pos) const{
    if (inpStr[pos] == '-') {
        if (pos + 1 >= inpStr.size() || !std::isdigit(inpStr[pos + 1])) {
            throw invalidSyntax(pos, inpStr);
        }
    }
    std::string number;
    number.push_back(inpStr[pos++]);
    int pointsCount = 0;
    while (pos < inpStr.size() && (std::isdigit(inpStr[pos]) || inpStr[pos] == '.')) {
        if (inpStr[pos] == '.') {
            if (++pointsCount > 1) {
                throw invalidSyntax(pos, inpStr);
            }
        }
        number.push_back(inpStr[pos++]);
    }
    if (inpStr[pos - 1] == '.') {
        throw invalidSyntax(pos, inpStr);
    }
    return number;
}
void Lexer::addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex) const{
    lexems[lexemIndex].first = "bracket";
    lexems[lexemIndex].second.push_back(bracket);
    ++pos;
}
void Lexer::addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex) const{
    if (std::isdigit(inputExpression[pos])) {
        --pos;
        addNumberToLexems(inputExpression, lexems, pos, lexemIndex);
    }
    else if (inputExpression[pos] == '{') {
        --pos;
        addMatrixToLexems(inputExpression, lexems, pos, lexemIndex);
    }
    else if (std::isalpha(inputExpression[pos]) || inputExpression[pos] == '(') {
        //problem with resize check later
        lexems[lexemIndex].first = "float";
        lexems[lexemIndex].second = "-1";
        lexems[++lexemIndex].first = "oper";
        lexems[lexemIndex].second = "*";
        if (inputExpression[pos] == '(') {
            return;
        }
        addVariableToLexems(inputExpression, lexems, pos, ++lexemIndex);
    }
    else {
        throw invalidSyntax(pos, inputExpression);
    }
}

bool Lexer::isValidMatrixSymbol(char symbol) const {

    return (std::isdigit(symbol) || symbol == '{' || symbol == '}' || symbol == ' ' || symbol == '-');
}

