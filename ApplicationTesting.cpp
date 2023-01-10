#include "ApplicationTesting.hpp"
#include "Evaluator.hpp"

void ApplicationTesting::runTestCases(const OperationRegistry& operationRegistry) {
    Evaluator evaluator(operationRegistry);
    std::ifstream testCases("../testCases");
    std::ofstream failedCases("../failedCases");
    std::string caseNumber;
    std::string caseExpression;
    std::string caseAnswer;
    std::vector<std::string> failedCaseNumbers;
    while (std::getline(testCases, caseNumber) && std::getline(testCases, caseExpression)
                                               && std::getline(testCases, caseAnswer)) {
        auto result = evaluator.evaluate(caseExpression);
        if (result->toString() != caseAnswer) {
            failedCases << caseNumber << std::endl << "expression - " << caseExpression << std::endl << "expected answer - ";
            failedCases << caseAnswer << std::endl << "received answer - " << result->toString() << std::endl;
            failedCaseNumbers.push_back(caseNumber);
        }
    }
        if (failedCaseNumbers.size() != 0) {
            std::cout << " testing failed for ";
        }
        for (auto & caseNumber : failedCaseNumbers) {
            std::cout << caseNumber << " ";
        }
        std::cout << std::endl;
}