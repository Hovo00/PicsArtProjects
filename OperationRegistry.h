#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <iostream>
#include <functional>
#include <memory>
#include "Matrix.h"
#include "Float.h"

namespace OperationRegistry {
    std::shared_ptr<Operand> matrixAddition(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatAddition(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixSubtract(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatSubtract(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> matrixMult(std::vector<std::shared_ptr<Operand> > arguments);
    std::shared_ptr<Operand> floatMult(std::vector<std::shared_ptr<Operand> > arguments);
    
    using FUNCTION = std::function<std::shared_ptr<Operand>(std::vector<std::shared_ptr<Operand> >)>;

    extern std::unordered_map<std::string, FUNCTION> operMap;
    extern void initializeOperationMap();
};

#endif