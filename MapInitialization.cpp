#include "MapInitialization.hpp"

void initEvaluatorOperationMap(Evaluator& evaluator) {
    evaluator.addOperator(MatrixOperations::matrixAddition, OperationKey("+", std::vector<std::string>{"matrix", "matrix"}), 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "matrix"}), 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "matrix"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixFloatDivision, OperationKey("/", std::vector<std::string>{"matrix", "float"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixEqual, OperationKey("==", std::vector<std::string>{"matrix", "matrix"}), 2, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(BoolOperations::questionMarkBool, OperationKey("?", std::vector<std::string>{"matrix"}), 1, Associativity::LeftToRight, Notation::Postfix);
    evaluator.addOperator(FloatOperations::thernardouble, OperationKey(":", std::vector<std::string>{"bool", "float", "float"}), 2, Associativity::RightToLeft, Notation::Infix);

    evaluator.addFunction(MatrixOperations::matrixInverse,OperationKey("inverse", std::vector<std::string>{"matrix"}));
    evaluator.addFunction(FloatOperations::sinus, OperationKey("sin", std::vector<std::string>{"float"}));
    evaluator.addFunction(FloatOperations::cosinus, OperationKey("cos", std::vector<std::string>{"float"}));
    evaluator.addFunction(MatrixOperations::matrixDeterminant, OperationKey("det", std::vector<std::string>{"matrix"}));
    evaluator.addFunction(MatrixOperations::Select, OperationKey("select", std::vector<std::string>{"matrix", "matrix", "matrix"}));
    evaluator.addFunction(MatrixOperations::matrixTranspose, OperationKey("transpose", std::vector<std::string>{"matrix"}));

    evaluator.addFunction(FloatOperations::doubleInverse, OperationKey("inverse", std::vector<std::string>{"float"}));
    evaluator.addOperator(FloatOperations::doubleAddition, OperationKey("+", std::vector<std::string>{"float", "float"}), 3, Associativity::LeftToRight, Notation::Infix );
    evaluator.addOperator(FloatOperations::doubleSubtraction, OperationKey("-", std::vector<std::string>{"float", "float"}), 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(FloatOperations::doubleDivision, OperationKey("/", std::vector<std::string>{"float", "float"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(FloatOperations::doubleMultiplication, OperationKey("*", std::vector<std::string>{"float", "float"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(FloatOperations::doubleEqual, OperationKey("==", std::vector<std::string>{"float", "float"}), 2, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(FloatOperations::questionMarkFloat, OperationKey("?", std::vector<std::string>{"float"}), 1, Associativity::LeftToRight, Notation::Postfix);
    evaluator.addOperator(MatrixOperations::matrixFloatMultiplication, OperationKey("*", std::vector<std::string>{"matrix", "float"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixFloatAddition, OperationKey("+", std::vector<std::string>{"matrix", "float"}), 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::matrixFloatSubtraction, OperationKey("-", std::vector<std::string>{"matrix", "float"}), 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(MatrixOperations::doubleMatrixMultiplication, OperationKey("*", std::vector<std::string>{"float", "matrix"}), 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    evaluator.addConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}