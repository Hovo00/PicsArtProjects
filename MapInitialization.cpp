#include "MapInitialization.hpp"
void initializeOperationMap(OperationRegistry& registry) {
    registry.addOperator("+", MatrixOperations::matrixAddition, OperationKey("+", std::vector<std::string>{"matrix", "matrix"}), 2, 3, Associativity::LeftToRight, Notation::Infix);
    registry.addOperator("-", MatrixOperations::matrixSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "matrix"}), 2, 3, Associativity::LeftToRight, Notation::Infix);
    registry.addOperator("*", MatrixOperations::matrixMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "matrix"}), 2, 4, Associativity::LeftToRight, Notation::Infix);
    registry.addOperator("/", MatrixOperations::matrixFloatDivision, OperationKey("/", std::vector<std::string>{"matrix", "float"}), 2, 4, Associativity::LeftToRight, Notation::Infix);
    registry.addOperator("==", MatrixOperations::matrixEqual, OperationKey("==", std::vector<std::string>{"matrix", "matrix"}), 2, 2, Associativity::LeftToRight, Notation::Infix);
    registry.addOperator("?", BoolOperations::questionMarkBool, OperationKey("?", std::vector<std::string>{"matrix"}), 1, 1, Associativity::LeftToRight, Notation::Postfix);
    registry.addOperator(":", FloatOperations::thernardouble, OperationKey(":", std::vector<std::string>{"bool", "float", "float"}), 3, 2, Associativity::RightToLeft, Notation::Infix);

    registry.addFunction("inverse", MatrixOperations::matrixInverse,OperationKey("inverse", std::vector<std::string>{"matrix"}), 1);
    registry.addFunction("sin", FloatOperations::sinus, OperationKey("sin", std::vector<std::string>{"float"}), 1);
    registry.addFunction("cos", FloatOperations::cosinus, OperationKey("cos", std::vector<std::string>{"float"}), 1);
    registry.addFunction("det", MatrixOperations::matrixDeterminant, OperationKey("det", std::vector<std::string>{"matrix"}), 1);
    registry.addFunction("select", MatrixOperations::Select, OperationKey("select", std::vector<std::string>{"matrix", "matrix", "matrix"}), 3);
    registry.addFunction("transpose", MatrixOperations::matrixTranspose, OperationKey("transpose", std::vector<std::string>{"matrix"}), 1);

    registry.addOperationOverload("inverse", FloatOperations::doubleInverse, OperationKey("inverse", std::vector<std::string>{"float"}));
    registry.addOperationOverload("+", FloatOperations::doubleAddition, OperationKey("+", std::vector<std::string>{"float", "float"}));
    registry.addOperationOverload("-", FloatOperations::doubleSubtraction, OperationKey("-", std::vector<std::string>{"float", "float"}));
    registry.addOperationOverload("/", FloatOperations::doubleDivision, OperationKey("/", std::vector<std::string>{"float", "float"}));
    registry.addOperationOverload("*", FloatOperations::doubleMultiplication, OperationKey("*", std::vector<std::string>{"float", "float"}));
    registry.addOperationOverload("==", FloatOperations::doubleEqual, OperationKey("==", std::vector<std::string>{"float", "float"}));
    registry.addOperationOverload("?", FloatOperations::questionMarkFloat, OperationKey("?", std::vector<std::string>{"float"}));
    registry.addOperationOverload("*", MatrixOperations::matrixFloatMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "float"}));
    registry.addOperationOverload("+", MatrixOperations::matrixFloatAddition, OperationKey("+", std::vector<std::string>{"matrix", "float"}));
    registry.addOperationOverload("-", MatrixOperations::matrixFloatSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "float"}));
    registry.addOperationOverload("*", MatrixOperations::doubleMatrixMultiplication, OperationKey("*", std::vector<std::string>{"float", "matrix"}));
    registry.addConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    registry.addConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}