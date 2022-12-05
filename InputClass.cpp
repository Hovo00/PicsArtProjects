#include "InputClass.h"

void ConsoleInput::getInput(std::string& inpStr){

   std::cout << "Enter expression: ";
   std::getline(std::cin, inpStr);

   //std::cout << inpStr;
}
