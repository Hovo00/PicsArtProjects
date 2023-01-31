#include "MapInitialization.hpp"

void initEvaluatorOperationMap(Evaluator& evaluator) {
    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "matrix"}), MatrixOperations::matrixAddition, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "matrix"}), MatrixOperations::matrixSubtraction, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "matrix"}), MatrixOperations::matrixMultiplication, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("/", std::vector<std::string>{"matrix", "float"}), MatrixOperations::matrixFloatDivision, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("==", std::vector<std::string>{"matrix", "matrix"}), MatrixOperations::matrixEqual, 2, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("?:", std::vector<std::string>{"bool", "float", "float"}), FloatOperations::thernardouble, 1, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("[|]", std::vector<std::string>{"bool", "float", "float", "float"}), FloatOperations::fornarydouble, 0, Associativity::LeftToRight, Notation::Infix);
    evaluator.addFunction(OperationSigniture("inverse", std::vector<std::string>{"matrix"}), MatrixOperations::matrixInverse);
    evaluator.addFunction(OperationSigniture("sin", std::vector<std::string>{"float"}), FloatOperations::sinus);
    evaluator.addFunction(OperationSigniture("cos", std::vector<std::string>{"float"}), FloatOperations::cosinus);
    evaluator.addFunction(OperationSigniture("det", std::vector<std::string>{"matrix"}), MatrixOperations::matrixDeterminant);
    evaluator.addFunction(OperationSigniture("select", std::vector<std::string>{"matrix", "matrix", "matrix"}), MatrixOperations::Select);
    evaluator.addFunction(OperationSigniture("transpose", std::vector<std::string>{"matrix"}), MatrixOperations::matrixTranspose);
    evaluator.addFunction(OperationSigniture("inverse", std::vector<std::string>{"float"}), FloatOperations::doubleInverse);

    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"float", "float"}), FloatOperations::doubleAddition, 3, Associativity::LeftToRight, Notation::Infix );
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"float", "float"}), FloatOperations::doubleSubtraction, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("/", std::vector<std::string>{"float", "float"}), FloatOperations::doubleDivision, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"float", "float"}), FloatOperations::doubleMultiplication, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("==", std::vector<std::string>{"float", "float"}), FloatOperations::doubleEqual, 2, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "float"}), MatrixOperations::matrixFloatMultiplication, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "float"}), MatrixOperations::matrixFloatAddition, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "float"}), MatrixOperations::matrixFloatSubtraction, 3, Associativity::LeftToRight, Notation::Infix);
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"float", "matrix"}), MatrixOperations::doubleMatrixMultiplication, 4, Associativity::LeftToRight, Notation::Infix);
    evaluator.addConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    evaluator.addConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}