#include "Input.hpp"

void ConsoleInput::getInput(Evaluator& evaluator, bool loopInputMode, std::string inputExpression){
    bool isLoopFirstIteration = true;
    do {
        auto result = evaluator.evaluate(inputExpression);
        ConsoleOutput::printResult(result->toString());
         if (isLoopFirstIteration && !loopInputMode){
            isLoopFirstIteration = false;
            continue;
         }
         ConsoleInput::_getInput(inputExpression);
         if (inputExpression == "quit") {
            break;
         }
      } while(loopInputMode);
}

void ConsoleInput::_getInput(std::string& inpStr){
   std::cout << std::endl << NOCOLOR <<"Enter expression : ";
   std::getline(std::cin, inpStr);
}