#include "MapInitialization.hpp"
void initEvaluatorOperationMap(Evaluator& evaluator) {
    evaluator.addOperator("+", MatrixOperations::matrixAddition, OperationKey("+", std::vector<std::string>{"matrix", "matrix"}), 2, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator("-", MatrixOperations::matrixSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "matrix"}), 2, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator("*", MatrixOperations::matrixMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "matrix"}), 2, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator("/", MatrixOperations::matrixFloatDivision, OperationKey("/", std::vector<std::string>{"matrix", "float"}), 2, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator("==", MatrixOperations::matrixEqual, OperationKey("==", std::vector<std::string>{"matrix", "matrix"}), 2, 2, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator("?", BoolOperations::questionMarkBool, OperationKey("?", std::vector<std::string>{"matrix"}), 1, 1, Associativity::LeftToRight, Notation::Postfix);
    evaluator.addOperator(":", FloatOperations::thernardouble, OperationKey(":", std::vector<std::string>{"bool", "float", "float"}), 3, 2, Associativity::RightToLeft, Notation::Infix);

    evaluator.addFunction("inverse", MatrixOperations::matrixInverse,OperationKey("inverse", std::vector<std::string>{"matrix"}), 1);
    evaluator.addFunction("sin", FloatOperations::sinus, OperationKey("sin", std::vector<std::string>{"float"}), 1);
    evaluator.addFunction("cos", FloatOperations::cosinus, OperationKey("cos", std::vector<std::string>{"float"}), 1);
    evaluator.addFunction("det", MatrixOperations::matrixDeterminant, OperationKey("det", std::vector<std::string>{"matrix"}), 1);
    evaluator.addFunction("select", MatrixOperations::Select, OperationKey("select", std::vector<std::string>{"matrix", "matrix", "matrix"}), 3);
    evaluator.addFunction("transpose", MatrixOperations::matrixTranspose, OperationKey("transpose", std::vector<std::string>{"matrix"}), 1);

    evaluator.addOperationOverload("inverse", FloatOperations::doubleInverse, OperationKey("inverse", std::vector<std::string>{"float"}));
    evaluator.addOperationOverload("+", FloatOperations::doubleAddition, OperationKey("+", std::vector<std::string>{"float", "float"}));
    evaluator.addOperationOverload("-", FloatOperations::doubleSubtraction, OperationKey("-", std::vector<std::string>{"float", "float"}));
    evaluator.addOperationOverload("/", FloatOperations::doubleDivision, OperationKey("/", std::vector<std::string>{"float", "float"}));
    evaluator.addOperationOverload("*", FloatOperations::doubleMultiplication, OperationKey("*", std::vector<std::string>{"float", "float"}));
    evaluator.addOperationOverload("==", FloatOperations::doubleEqual, OperationKey("==", std::vector<std::string>{"float", "float"}));
    evaluator.addOperationOverload("?", FloatOperations::questionMarkFloat, OperationKey("?", std::vector<std::string>{"float"}));
    evaluator.addOperationOverload("*", MatrixOperations::matrixFloatMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "float"}));
    evaluator.addOperationOverload("+", MatrixOperations::matrixFloatAddition, OperationKey("+", std::vector<std::string>{"matrix", "float"}));
    evaluator.addOperationOverload("-", MatrixOperations::matrixFloatSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "float"}));
    evaluator.addOperationOverload("*", MatrixOperations::doubleMatrixMultiplication, OperationKey("*", std::vector<std::string>{"float", "matrix"}));
    evaluator.addConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    evaluator.addConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}