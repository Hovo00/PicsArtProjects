#include "LexerFunctions.hpp"
#include <cctype>

void LexerFunctions::addNumberToLexems(const std::string& inpStr, LexerFunctions::VectorOfLexems& lexems, int& pos, int& lexemIndex,
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
void LexerFunctions::addVariableToLexems(const std::string& inpStr, LexerFunctions::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
    lexems[lexemIndex].first = "var";
    while (pos < inpStr.size() && std::isalpha(inpStr[pos])) {
        lexems[lexemIndex].second.push_back(inpStr[pos++]);
    }
    if (isFunction(lexems[lexemIndex].second)) {
        addFunctionToLexems(inpStr, lexems, pos, lexemIndex, registry);
        return;
    }
    if (pos == inpStr.size()) {
        ++lexemIndex;
        return;
    }
    //here error
    if (inpStr[pos] != ' ' && !isOperatorSymbol(inpStr[pos]) && inpStr[pos] != ')' && inpStr[pos] != ',') {
        if (!isFunction(lexems[lexemIndex].second)) {
            throw InvalidVariable(pos, inpStr);
        }
    }
    ++lexemIndex;
}

void LexerFunctions::addMatrixToLexems(const std::string& inpStr, LexerFunctions::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
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

void LexerFunctions::addOperatorToLexems(const std::string& inpStr, LexerFunctions::VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
    std::string Operator;
    while (pos < inpStr.size() && isOperatorSymbol(inpStr[pos])) {
        Operator.push_back(inpStr[pos++]);
    }
    if (!isOperator(Operator) || (pos == inpStr.size() &&
        registry.operationInfo(Operator).notation != Notation::Postfix)) {
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
        if (!isFunction(lexems[lexemIndex - 1].second)) {
            throw invalidSyntax(pos - 1, inpStr);
        }
    }

    //oterwise its normal case , as 4 * 5 or 4 - 5
    lexems[lexemIndex].first = "oper";
    lexems[lexemIndex].second = Operator;
    ++lexemIndex;
}
void LexerFunctions::addFunctionToLexems(const std::string& inpStr, LexerFunctions::VectorOfLexems& lexems, int& pos, int& lexemCount, 
                                const OperationRegistry& registry) {
    if (inpStr[pos++] != '(') {
        throw invalidSyntax(pos, inpStr);
    }
    lexems[lexemCount].first = "oper";
    int argCount = registry.operationInfo(lexems[lexemCount++].second).argumentCount;
    int commasCount = 0;
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
std::string LexerFunctions::cutNumberFromExpression(const std::string& inpStr, int& pos,
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
void LexerFunctions::addBracketToLexems(char bracket, VectorOfLexems& lexems, int& pos, int lexemIndex, const OperationRegistry& registry) {
    lexems[lexemIndex].first = "bracket";
    lexems[lexemIndex].second.push_back(bracket);
    ++pos;
}
void LexerFunctions::addNegativeLexem(const std::string& inputExpression, VectorOfLexems& lexems, int& pos, int& lexemIndex, const OperationRegistry& registry) {
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
bool LexerFunctions::isValidMatrixSymbol(char symbol) {
    return (std::isdigit(symbol) || symbol == '{' || symbol == '}' || symbol == ' ' || symbol == '-');
}

bool LexerFunctions::isNumber(const std::string& inputExpression, const VectorOfLexems& lexems, int pos, int lexemIndex,
                                const OperationRegistry& registry) {
    return std::isdigit(inputExpression[pos]);
}