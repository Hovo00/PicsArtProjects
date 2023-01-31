#include "Lexer.hpp"
#include "Exception.hpp"
#include "OperationRegistry.hpp"
#include <algorithm>
#include <exception>
#include <string>

Lexer::VectorOfLexems Lexer::divideTolexems(const std::string& inpStr, const OperationRegistry& registry){
    Lexer::VectorOfLexems lexems;
    lexems.resize(inpStr.size() * 2);
    int lexemCount = 0;
    int i = 0;
    while (i < inpStr.size()) {
        if (std::isdigit(inpStr[i])) {
            addNumberToLexems(inpStr, lexems, i, lexemCount, registry);
        }
        else if (std::isalpha(inpStr[i])) {
            addVariableToLexems(inpStr, lexems, i, lexemCount, registry);
        }
        else if (inpStr[i] == '{') {
            addMatrixToLexems(inpStr, lexems, i, lexemCount, registry);
        }
        else if (isOperatorSymbol(inpStr[i])) {
            addOperatorToLexems(inpStr, lexems, i, lexemCount, registry);
        }
        else if (inpStr[i] == '(' || inpStr[i] == ')') {
            addBracketToLexems(inpStr[i], lexems, i, lexemCount, registry);
            ++lexemCount;
        }
        else if (inpStr[i] == ' ') {
            ++i;
        }
        else {
            throw invalidSyntax(i, inpStr);
        }
    }
    if (lexemCount == 0) {
       throw EmptyExpression();
    }
    lexems.resize(lexemCount);
    initializeVariables(lexems, registry);
    return infixToPostfix(lexems, registry);
}

void Lexer::addNumberToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex,
                              const OperationRegistry& registry) {
    lexems[lexemIndex].first = "float";
    lexems[lexemIndex].second = cutNumberFromExpression(inpStr, pos, registry);
    ++lexemIndex;
    if (pos == inpStr.size()) {
        return;
    }
    if (!isOperatorSymbol(inpStr[pos]) && inpStr[pos] != ')' && inpStr[pos] != ' ' && inpStr[pos] != ',') {
        throw invalidSyntax(pos, inpStr);
    }
}
void Lexer::addVariableToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
    lexems[lexemIndex].first = "var";
    while (pos < inpStr.size() && std::isalpha(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (isFunction(lexems[lexemIndex].second, registry)) {
        addFunctionToLexems(inpStr, lexems, pos, lexemIndex, registry);
        return;
    }
    if (pos == inpStr.size()) {
        ++lexemIndex;
        return;
    }
    //here error
    if (inpStr[pos] != ' ' && !isOperatorSymbol(inpStr[pos]) && inpStr[pos] != ')' && inpStr[pos] != ',') {
        if (!isFunction(lexems[lexemIndex].second, registry)) {
            throw InvalidVariable(pos, inpStr);
        }
    }
    ++lexemIndex;
}

void Lexer::addMatrixToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry){
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
            lexems[lexemIndex].second += cutNumberFromExpression(inpStr, pos, registry);
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

void Lexer::addOperatorToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
    std::string Operator;
    while (pos < inpStr.size() && isOperatorSymbol(inpStr[pos])) {
        Operator.push_back(inpStr[pos++]);
    }
    if (isSeparator(Operator)) {
        lexems[lexemIndex].first = "separator";
        lexems[lexemIndex].second = Operator;
        ++lexemIndex;
        return;
    }
    if ((!isOperator(Operator, registry) || (pos == inpStr.size()) &&
        registry.operationInfo(Operator).second.notation != Notation::Postfix) &&
        !isSeparator(Operator)) {
        throw invalidSyntax(pos, inpStr);
    }
    if (Operator == "-") {
        // check does it something like , -4 or 5 + -4 (allowed cases)
        if (lexemIndex == 0 || lexemIndex > 0 && (lexems[lexemIndex - 1].first == "oper" || lexems[lexemIndex - 1].second == "(")) {
            addNegativeLexem(inpStr, lexems, pos, lexemIndex, registry);
            return;
        }
    }
    // such cases as,  * 5 or 4 + * 5 are not allowed
    else if (lexemIndex == 0 || lexemIndex > 0 && lexems[lexemIndex - 1].first == "oper") {
        if (!isFunction(lexems[lexemIndex - 1].second, registry)) {
            throw invalidSyntax(pos - 1, inpStr);
        }
    }

    //oterwise its normal case , as 4 * 5 or 4 - 5
    lexems[lexemIndex].first = "oper";
    lexems[lexemIndex].second = Operator;
    ++lexemIndex;
}

Lexer::VectorOfLexems Lexer::infixToPostfix(const Lexer::VectorOfLexems& infix, const OperationRegistry& registry) {
    // for(auto & i : infix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    //  std::cout << std::endl;
    Lexer::VectorOfLexems postfix;
    std::stack<std::pair<std::string, std::string> > st;
    for (const auto& lexem : infix) {
        if (lexem.first == "oper" || lexem.first == "separator") {
           if (lexem.first == "separator") {
                updateCount(lexem.second);
                while (!st.empty() && st.top().second != "(" &&
                       precedence(st.top().second, registry) > precedence(lexem.second, registry)
                       ) {
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (getSeparator(lexem.second).empty()) {
                    st.push(lexem);
                }
                else {
                    if (st.top().second != getSeparator(lexem.second)) {
                        while (!st.empty() && st.top().second != getSeparator(lexem.second) && st.top().second != "(") {
                            postfix.push_back(st.top());
                            st.pop();
                        }
                        st.pop();
                        st.push(lexem);
                        //throw std::string("something wrong");
                    }
                    else {
                        st.pop();
                        st.push(lexem);
                    }
                }
           }
           else if (isMultiOperandOperator(lexem.second)) {
            //optimize
                auto res = getSeparator(lexem.second);
                updateCount(lexem.second);
                while (!st.empty() && st.top().second != res) {
                    postfix.push_back(st.top());
                    st.pop();
                }
                //here check
                st.pop();
                if (getCount(lexem.second) > 0) {
                    while (!st.empty() && isOperator(st.top().second, registry) && precedence(st.top().second , registry) >= precedence(lexem.second , registry)) {
                        postfix.push_back(st.top());
                        st.pop();
                    }
                }
                st.push(lexem);
           }
            else if (st.empty()) {
                st.push(lexem);
            }
            else if (st.top().first != "oper" ||
                    precedence(st.top().second, registry) < precedence(lexem.second, registry)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && st.top().first == "oper" &&
                      precedence(st.top().second, registry) >= precedence(lexem.second, registry)) {
                    if (precedence(st.top().second, registry) < precedence(lexem.second, registry) &&
                         registry.operationInfo(st.top().second).second.associativity == Associativity::RightToLeft) {
                        break;
                    }
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (st.empty() && registry.operationInfo(lexem.second).second.associativity == Associativity::LeftToRight &&
                    registry.operationInfo(lexem.second).second.notation == Notation::Postfix) {
                    postfix.push_back(lexem);
                    }
                st.push(lexem);
            }
        }
        else if (lexem.second == "(") {
            st.push(lexem);
        }
        else if (lexem.second == ")" || lexem.first == "comma") {
            while (!st.empty() && st.top().second != "(") {
                postfix.push_back(st.top());
                st.pop();
            }
            if (!st.empty() && lexem.second == ")") {
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
        std::cout << i.second << " "  << i.first << std::endl;
    }
    return postfix;
}

void Lexer::initializeVariables(Lexer::VectorOfLexems& lexems, const OperationRegistry& registry) {
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
            inputVariable(lexems, i, registry);
        }
    }
}

void Lexer::inputVariable(Lexer::VectorOfLexems& lexems, int lexemIndex, const OperationRegistry& registry) {
    std::string userInput;
    std::cout << "Enter variable " << lexems[lexemIndex].second << " ";
    std::getline(std::cin, userInput);
    int i = 0;
    lexems[lexemIndex].second = "";
    if (std::isdigit(userInput[i])) {
        addNumberToLexems(userInput, lexems, i, lexemIndex, registry);
    }
    else if (userInput[0] == '{') {
        addMatrixToLexems(userInput, lexems, i, lexemIndex, registry);
    }
    else {
        throw invalidSyntax(i, userInput);
    }
}

void Lexer::addFunctionToLexems(const std::string& inpStr, Lexer::VectorOfLexems& lexems, int& pos, int& lexemCount,
                                const OperationRegistry& registry) {
    if (inpStr[pos++] != '(') {
        throw invalidSyntax(pos, inpStr);
    }
    lexems[lexemCount].first = "oper";
    int argCount = registry.operationInfo(lexems[lexemCount++].second).second.argumentCount;
    int commasCount = 0;
    lexems[lexemCount].first = "bracket";
    lexems[lexemCount++].second = "(";
    while (inpStr[pos] != ')' && pos < inpStr.size()) {
        if (std::isdigit(inpStr[pos])) {
            addNumberToLexems(inpStr, lexems, pos, lexemCount, registry);
        }
        else if (inpStr[pos] == '{') {
            addMatrixToLexems(inpStr, lexems, pos, lexemCount, registry);
        }
        else if (std::isalpha(inpStr[pos])) {
            addVariableToLexems(inpStr, lexems, pos, lexemCount, registry);
        }
        else if (isOperatorSymbol(inpStr[pos])) {
            addOperatorToLexems(inpStr, lexems, pos, lexemCount, registry);
        }
        else if (inpStr[pos] == ',') {
            if (++commasCount == argCount) {
                //change exception
                throw invalidSyntax(pos, inpStr);
            }
        lexems[lexemCount].first = "comma";
        lexems[lexemCount++].second = "comma";
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
    lexems[lexemCount].first = "bracket";
    lexems[lexemCount++].second = ")";
    ++pos;
}
std::string Lexer::cutNumberFromExpression(const std::string& inpStr, int& pos,
                                           const OperationRegistry& registry) {
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
void Lexer::addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex, const OperationRegistry& registry) {
    lexems[lexemIndex].first = "bracket";
    lexems[lexemIndex].second.push_back(bracket);
    ++pos;
}
void Lexer::addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
    if (std::isdigit(inputExpression[pos])) {
        --pos;
        addNumberToLexems(inputExpression, lexems, pos, lexemIndex, registry);
    }
    else if (inputExpression[pos] == '{') {
        --pos;
        addMatrixToLexems(inputExpression, lexems, pos, lexemIndex, registry);
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
        addVariableToLexems(inputExpression, lexems, pos, ++lexemIndex, registry);
    }
    else {
        throw invalidSyntax(pos, inputExpression);
    }
}

bool Lexer::isValidMatrixSymbol(char symbol) {

    return (std::isdigit(symbol) || symbol == '{' || symbol == '}' || symbol == ' ' || symbol == '-');
}
bool Lexer::isOperator(const std::string& expression, const OperationRegistry& registry) {
    return registry.existOperation(expression);
}
bool Lexer::isFunction(const std::string& expression, const OperationRegistry& registry) {
    return (registry.existOperation(expression) &&
            registry.operationInfo(expression).second.operationType == OperationType::Function);
}
bool Lexer::isOperatorSymbol(char symbol) const {
    return std::find(_symbolRegistry.begin(), _symbolRegistry.end(), symbol) != _symbolRegistry.end() ||
           isSeparator(std::string{symbol});
}
void Lexer::registerSymbols(const OperationSigniture& signiture) {
    if (signiture.argumentsType.size() > 2) {
        if (signiture.operationName.size() != signiture.argumentsType.size() - 1) {
            throw std::string("Characters count of Operator which have more then 2 arguments must be equal to argument count - 1");
        }
        //add checking
        _separatorRegistry.push_back(std::make_pair(signiture.operationName, 0));
        _symbolRegistry.push_back(signiture.operationName.back());
        return;
    }
    for (const auto & symbol : signiture.operationName) {
        if (std::find(_symbolRegistry.begin(), _symbolRegistry.end(), symbol) == _symbolRegistry.end()) {
            _symbolRegistry.push_back(symbol);
        }
    }
}
bool Lexer::isSeparator(const std::string& expression) const{
    //assume for simplicity separator have one symbol
    char separator = expression[0];
    for (const auto& reg : _separatorRegistry) {
        int size = reg.first.size() - 1;
        for (int i = 0; i < size; ++i) {
            if (reg.first[i] == separator) {
                return true;
            }
        }
    }
    return false;
}

int Lexer::separatorPrec(const std::string& separator, const OperationRegistry& registry) {
    char sep = separator[0];
    for (const auto& reg : _separatorRegistry) {
        if (std::find(reg.first.begin(), reg.first.end(), sep) != reg.first.end()) {
            return registry.operationInfo(std::string{reg.first.back()}).second.precedence;
        }
    }
    return 0;
}

int Lexer::precedence(const std::string& operation, const OperationRegistry& registry) {
    if (isSeparator(operation)) {
        return separatorPrec(operation, registry);
    }
    else {
        return registry.operationInfo(operation).second.precedence;
    }
}
bool Lexer::isMultiOperandOperator(const std::string& exprik) {
    char iso = exprik[0];
    for (const auto& reg : _separatorRegistry) {
        if (reg.first.back() == iso) {
            return true;
        }
    }
    return false;
}
void Lexer::updateCount(const std::string& symbol) {
    char symb = symbol[0];
    for (auto & reg : _separatorRegistry) {
        auto it = std::find(reg.first.begin(), reg.first.end(), symb);
        if (it != reg.first.end()) {
            reg.second += *it == reg.first.back() ? -reg.first.size() : 1;
        }
    }
}
int Lexer::getCount(const std::string& symbol) {
    char symb = symbol[0];
    for (auto & reg : _separatorRegistry) {
        if (std::find(reg.first.begin(), reg.first.end(), symb) != reg.first.end()) {
            return reg.second;
        }
    }
    return 0;
}

std::string Lexer::getSeparator(const std::string& symbol) {
    char symb = symbol[0];
    for (const auto& reg : _separatorRegistry) {
        for (int i = 0; i < reg.first.size(); ++i) {
            if (reg.first[i] == symb && i > 0) {
                return std::string{reg.first[i-1]};
            }
        }
    }
    return "";
}

