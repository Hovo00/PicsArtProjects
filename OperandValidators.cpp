#include "OperandValidators.hpp"

std::string Validators::validateFloat(const std::string& inputExpr, int& pos) {
    if (!std::isdigit(inputExpr[pos])) {
        return "";
    }
    std::string lexem;
    lexem = cutNumberFromExpression(inputExpr, pos);
    // if (pos == inputExpr.size()) {
    //     return lexem;
    // }
    return lexem;
}
std::string Validators::validateMatrix(const std::string& inputExpr, int& pos) {
    if (inputExpr[pos] != '{') {
        return "";
    }
    std::string lexem;
    if (inputExpr[pos] == '-') {
        lexem.push_back(inputExpr[pos++]);
    }
    lexem.push_back(inputExpr[pos++]);
    int closingBrecketsExpected = 1;
    int openingBrecketsCount = 1;
    int closingBrecketsCount = 0;
    int dimension = 0;
    int currentRawElementsCount = 0;
    while (pos < inputExpr.size() && closingBrecketsExpected != 0) {
        if(!isValidMatrixSymbol(inputExpr[pos])) {
            throw InvalidMatrixOperand(pos, inputExpr);
        }
        if (inputExpr[pos] == '-' || std::isdigit(inputExpr[pos])) {
            lexem += cutNumberFromExpression(inputExpr, pos);
            if (pos == inputExpr.size()) {
                throw invalidSyntax(pos, inputExpr);
            }
            if (inputExpr[pos] != '}' && inputExpr[pos] != ' ') {
                throw invalidSyntax(pos, inputExpr);
            }
            if (openingBrecketsCount < 3) {
                ++dimension;
            }
            ++currentRawElementsCount;
        }
        else if (inputExpr[pos] == '{') {
            ++closingBrecketsExpected;
            ++openingBrecketsCount;
            if (openingBrecketsCount - closingBrecketsCount > 2) {
                throw invalidSyntax(pos, inputExpr);
            }
            lexem.push_back(inputExpr[pos++]);
        }
        else if (inputExpr[pos] == '}') {
            --closingBrecketsExpected;
            ++closingBrecketsCount;
            if (currentRawElementsCount != dimension && closingBrecketsExpected != 0) {
               throw WrondMatrixDimension(pos, dimension, currentRawElementsCount, inputExpr);
            }
            currentRawElementsCount = 0;
            lexem.push_back(inputExpr[pos++]);
        }
        else if (inputExpr[pos] == ' ') {
            lexem.push_back(inputExpr[pos++]);
        }
    }
    return lexem;
}
std::string Validators::cutNumberFromExpression(const std::string& inputExpr, int& pos) {

    if (inputExpr[pos] == '-') {
        if (pos + 1 >= inputExpr.size() || !std::isdigit(inputExpr[pos + 1])) {
            throw invalidSyntax(pos, inputExpr);
        }
    }
    std::string number;
    number.push_back(inputExpr[pos++]);
    int pointsCount = 0;
    while (pos < inputExpr.size() && (std::isdigit(inputExpr[pos]) || inputExpr[pos] == '.')) {
        if (inputExpr[pos] == '.') {
            if (++pointsCount > 1) {
                throw invalidSyntax(pos, inputExpr);
            }
        }
        number.push_back(inputExpr[pos++]);
    }
    if (inputExpr[pos - 1] == '.') {
        throw invalidSyntax(pos, inputExpr);
    }
    return number;
}
bool Validators::isValidMatrixSymbol(char symbol) {
    return (std::isdigit(symbol) || symbol == '{' || symbol == '}' || symbol == ' ' || symbol == '-');
}
