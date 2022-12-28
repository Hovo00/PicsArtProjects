#include "BoolOperations.h"

std::shared_ptr<Operand> BoolOperations::questionMarkBool(const std::vector<std::shared_ptr<Operand> >& arguments) {
    auto boolean = std::static_pointer_cast<Bool>(arguments[0]);
    return std::make_shared<Bool>(boolean->getValue());
}


// == int int  
//bool -> (int)
//int -> matrix, bool 
//matrix -> int