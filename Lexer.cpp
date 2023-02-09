#include "Lexer.hpp"
#include "Exception.hpp"
#include "OperationRegistry.hpp"
#include <algorithm>
#include <exception>
#include <string>

Lexer::VectorOfLexems Lexer::divideTolexems(const std::string& inputExpr, const OperationRegistry& registry){
    _inputExpression = inputExpr;
    _lexems.resize(0);
    _lexems.resize(_inputExpression.size() * 2);
    int lexemCount = 0;
    int i = 0;
    while (i < _inputExpression.size()) {
        bool isOperand = false;
        for (auto & validator : _operandValidators) {
            int pos = i;
            auto res = validator.second(_inputExpression, pos);
            if (res != "") {
                isOperand = true;
                i = pos;
                _lexems[lexemCount].first = validator.first;
                _lexems[lexemCount].second = res;
                ++lexemCount;
                if (!isOperatorSymbol(_inputExpression[i]) && _inputExpression[i] != ')' && _inputExpression[i] != ' '
                    && _inputExpression[i] != ',' && i < _inputExpression.size()) {
                    throw invalidSyntax(i, _inputExpression);
                }
                break;
            }
        }
        if (isOperand) {
            continue;
        }
        else if (std::isalpha(_inputExpression[i])) {
            addVariableToLexems(i, lexemCount, registry);
        }
        else if (isOperatorSymbol(_inputExpression[i])) {
            addOperatorToLexems(i, lexemCount, registry);
        }
        else if (_inputExpression[i] == '(' || _inputExpression[i] == ')') {
            _lexems[lexemCount].first = "bracket";
            _lexems[lexemCount].second.push_back(_inputExpression[i]);
            ++i;
            ++lexemCount;
        }
        else if (_inputExpression[i] == ' ') {
            ++i;
        }
        else {
            throw invalidSyntax(i, _inputExpression);
        }
    }
    if (lexemCount == 0) {
       throw EmptyExpression();
    }
    _lexems.resize(lexemCount);
    initializeVariables(registry);
    return infixToPostfix(registry);
}

void Lexer::addVariableToLexems(int& pos, int& lexemIndex, const OperationRegistry& registry) {
    _lexems[lexemIndex].first = "var";
    while (pos < _inputExpression.size() && std::isalpha(_inputExpression[pos])) {
        _lexems[lexemIndex].second.push_back(_inputExpression[pos++]);
    }
    if (isFunction(_lexems[lexemIndex].second, registry)) {
        addFunctionToLexems(pos, lexemIndex, registry);
        return;
    }
    if (pos == _inputExpression.size()) {
        ++lexemIndex;
        return;
    }
    //here error
    if (_inputExpression[pos] != ' ' && !isOperatorSymbol(_inputExpression[pos]) && _inputExpression[pos] != ')' && _inputExpression[pos] != ',') {
        if (!isFunction(_lexems[lexemIndex].second, registry)) {
            throw InvalidVariable(pos, _inputExpression);
        }
    }
    ++lexemIndex;
}

void Lexer::addOperatorToLexems(int& pos, int& lexemIndex, const OperationRegistry& registry) {
    std::string Operator;
    while (pos < _inputExpression.size() && isOperatorSymbol(_inputExpression[pos])) {
        Operator.push_back(_inputExpression[pos++]);
    }
    if (isSeparator(Operator)) {
        _lexems[lexemIndex].first = "separator";
        _lexems[lexemIndex].second = Operator;
        ++lexemIndex;
        return;
    }
    if ((!isOperator(Operator, registry) || (pos == _inputExpression.size()) &&
        registry.operationInfo(Operator).second.notation != Notation::Postfix) &&
        !isSeparator(Operator)) {
        throw invalidSyntax(pos, _inputExpression);
    }
    if (Operator == "-") {
        // check does it something like , -4 or 5 + -4 (allowed cases)
        if (lexemIndex == 0 || lexemIndex > 0 && (_lexems[lexemIndex - 1].first == "oper" || _lexems[lexemIndex - 1].second == "(")) {
            addNegativeLexem(pos, lexemIndex, registry);
            return;
        }
    }
    // such cases as,  * 5 or 4 + * 5 are not allowed
    else if (lexemIndex == 0 || lexemIndex > 0 && _lexems[lexemIndex - 1].first == "oper") {
        if (!isFunction(_lexems[lexemIndex - 1].second, registry)) {
            throw invalidSyntax(pos - 1, _inputExpression);
        }
    }

    //oterwise its normal case , as 4 * 5 or 4 - 5
    _lexems[lexemIndex].first = "oper";
    _lexems[lexemIndex].second = Operator;
    ++lexemIndex;
}

Lexer::VectorOfLexems Lexer::infixToPostfix(const OperationRegistry& registry) {
    // for(auto & i : infix) {
    //      std::cout << i.second << " "  << i.first << std::endl;
    //  }
    //  std::cout << std::endl;
    Lexer::VectorOfLexems postfix;
    std::stack<std::pair<std::string, std::string> > st;
    for (const auto& lexem : _lexems) {
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
    // for(auto & i : postfix) {
    //     std::cout << i.second << " "  << i.first << std::endl;
    // }
    return postfix;
}

void Lexer::initializeVariables(const OperationRegistry& registry) {
    std::unordered_map<std::string, int> knownVariables;
    for (int i = 0; i < _lexems.size(); ++i) {
        if (_lexems[i].first == "var") {
            if (knownVariables.find(_lexems[i].second) != knownVariables.end()) {
                int j = knownVariables[_lexems[i].second];
                _lexems[i].first = _lexems[j].first;
                _lexems[i].second = _lexems[j].second;
                continue;
            }
            knownVariables[_lexems[i].second] = i;
            inputVariable(i, registry);
        }
    }
}

void Lexer::inputVariable(int lexemIndex, const OperationRegistry& registry) {
    std::string userInput;
    std::cout << "Enter variable " << _lexems[lexemIndex].second << " ";
    std::getline(std::cin, userInput);
    int i = 0;
    _lexems[lexemIndex].second = "";
    bool isOperand = false;
    for (auto & validator : _operandValidators) {
        auto res = validator.second(userInput, i);
        if (res != "") {
            _lexems[lexemIndex].first = validator.first;
            _lexems[lexemIndex].second = res;
            isOperand = true;
            break;
        }
    }

    if (!isOperand){
        throw invalidSyntax(i, userInput);
    }
}

void Lexer::addFunctionToLexems(int& pos, int& lexemCount,
                                const OperationRegistry& registry) {
    if (_inputExpression[pos++] != '(') {
        throw invalidSyntax(pos, _inputExpression);
    }
    _lexems[lexemCount].first = "oper";
    int argCount = registry.operationInfo(_lexems[lexemCount++].second).second.argumentCount;
    int commasCount = 0;
    _lexems[lexemCount].first = "bracket";
    _lexems[lexemCount++].second = "(";
    while (_inputExpression[pos] != ')' && pos < _inputExpression.size()) {
        bool isOperand = false;
        for (auto & validator : _operandValidators) {
            auto res = validator.second(_inputExpression, pos);
            if (res != "") {
                _lexems[lexemCount].first = validator.first;
                _lexems[lexemCount].second = res;
                ++lexemCount;
                isOperand = true;
                break;
            }
        }
        if (isOperand) {
            continue;
        }
        else if (std::isalpha(_inputExpression[pos])) {
            addVariableToLexems(pos, lexemCount, registry);
        }
        else if (isOperatorSymbol(_inputExpression[pos])) {
            addOperatorToLexems(pos, lexemCount, registry);
        }
        else if (_inputExpression[pos] == ',') {
            if (++commasCount == argCount) {
                //change exception
                throw invalidSyntax(pos, _inputExpression);
            }
        _lexems[lexemCount].first = "comma";
        _lexems[lexemCount++].second = "comma";
        ++pos;
        }
        else if (_inputExpression[pos] == ' ') {
            ++pos;
        }
        else {
            throw invalidSyntax(pos, _inputExpression);
        }
    }
    if (argCount - commasCount != 1) {
        throw invalidSyntax(pos, _inputExpression);
    }
    if (_inputExpression[pos] != ')') {
        throw invalidSyntax(pos, _inputExpression);
    }
    _lexems[lexemCount].first = "bracket";
    _lexems[lexemCount++].second = ")";
    ++pos;
}

void Lexer::addNegativeLexem(int& pos, int& lexemIndex, const OperationRegistry& registry) {
    bool isOperand = false;
        for (auto & validator : _operandValidators) {
            auto res = validator.second(_inputExpression, pos);
            if (res != "") {
                _lexems[lexemIndex].first = validator.first;
                _lexems[lexemIndex].second = "-" + res;
                ++lexemIndex;
                isOperand = true;
                break;
            }
        }
    if (isOperand) {

    }
    else if (std::isalpha(_inputExpression[pos]) || _inputExpression[pos] == '(') {
        //problem with resize check later
        _lexems[lexemIndex].first = "float";
        _lexems[lexemIndex].second = "-1";
        _lexems[++lexemIndex].first = "oper";
        _lexems[lexemIndex].second = "*";
        if (_inputExpression[pos] == '(') {
            return;
        }
        addVariableToLexems(pos, ++lexemIndex, registry);
    }
    else {
        throw invalidSyntax(pos, _inputExpression);
    }
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



int Lexer::precedence(const std::string& operation, const OperationRegistry& registry) {
    if (isSeparator(operation)) {
        char sep = operation[0];
        for (const auto& reg : _separatorRegistry) {
            if (std::find(reg.first.begin(), reg.first.end(), sep) != reg.first.end()) {
                return registry.operationInfo(std::string{reg.first.back()}).second.precedence;
            }
        }
        return 0;
    }
    else {
        return registry.operationInfo(operation).second.precedence;
    }
}
bool Lexer::isMultiOperandOperator(const std::string& expression) {
    char symbol = expression[0];
    for (const auto& reg : _separatorRegistry) {
        if (reg.first.back() == symbol) {
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
void Lexer::registerValidator(const std::string& operandName, Validator validator) {
    _operandValidators.push_back(std::make_pair(operandName, validator));
}

