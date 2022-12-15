#include "Output.h"

void ConsoleOutput::showErrorPlace(const std::string& errorMessage, const std::string& inputExpression, int pos) {
    printErrorMessage(errorMessage);
    std::cout << std::endl << RED << inputExpression << std::endl;
    std::cout << GREEN << std::setw(pos + 10) << "^~~~~~~~~~" << std::endl;
    std::cout << NOCOLOR << std::endl;
}
void ConsoleOutput::printErrorMessage(const std::string& errorMessage) {
    std::cout << "\n\n" << REDWHITE << errorMessage;
    std::cout << NOCOLOR << std::endl << std::endl;
}