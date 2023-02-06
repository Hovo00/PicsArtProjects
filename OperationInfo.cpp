#include "OperationInfo.hpp"

Properties::Properties(int prec, Associativity assoc, Notation note) {
    precedence = prec;
    associativity = assoc;
    notation = note;
}


OperationProperties::OperationProperties(Properties props,
                                        OperationType type,
                                        int argCount) : Properties(props),
                                                        operationType(type),
                                                        argumentCount(argCount) {

}