#include "Output.hpp"

void ConsoleOutput::showErrorPlace(const std::string& errorMessage, const std::string& inputExpression, int pos) {
    printErrorMessageRedWhite(errorMessage);
    std::cout << std::endl << RED << inputExpression << std::endl;
    std::cout << GREEN << std::setw(pos + 10) << "^~~~~~~~~~" << std::endl;
    std::cout << NOCOLOR << std::endl;
}
void ConsoleOutput::printErrorMessageRedWhite(const std::string& errorMessage) {
    std::cout << "\n\n" << REDWHITE << errorMessage;
    std::cout << NOCOLOR << std::endl << std::endl;
}
void ConsoleOutput::printErrorMessageRed(const std::string& errorMessage) {
    std::cout << "\n\n" << RED << errorMessage;
    std::cout << NOCOLOR << std::endl << std::endl;
}
void ConsoleOutput::printResult(const std::string& result) {
    std::cout << "\n\n" << GREEN << "Result :  " << result;
    std::cout << std::endl;
}

