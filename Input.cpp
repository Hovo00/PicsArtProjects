#include "Input.hpp"

void ConsoleInput::getInput(std::string& inpStr){
   std::cout << "Enter expression : ";
   std::getline(std::cin, inpStr);
}
