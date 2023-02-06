#include "MapInitialization.hpp"

void initEvaluatorOperationMap(Evaluator& evaluator) {
    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("/", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatDivision, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("==", std::vector<std::string>{"matrix", "matrix"}), "bool", MatrixOperations::matrixEqual, Properties{2, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("?:", std::vector<std::string>{"bool", "float", "float"}), "float", FloatOperations::thernardouble, Properties{1, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("[|]", std::vector<std::string>{"bool", "float", "float", "float"}), "float", FloatOperations::fornarydouble, Properties{0, Associativity::LeftToRight, Notation::Infix});
    evaluator.addFunction(OperationSigniture("inverse", std::vector<std::string>{"matrix"}), "matrix",  MatrixOperations::matrixInverse);
    evaluator.addFunction(OperationSigniture("sin", std::vector<std::string>{"float"}), "float", FloatOperations::sinus);
    evaluator.addFunction(OperationSigniture("cos", std::vector<std::string>{"float"}), "float", FloatOperations::cosinus);
    evaluator.addFunction(OperationSigniture("det", std::vector<std::string>{"matrix"}), "float", MatrixOperations::matrixDeterminant);
    evaluator.addFunction(OperationSigniture("select", std::vector<std::string>{"matrix", "matrix", "matrix"}), "matrix", MatrixOperations::Select);
    evaluator.addFunction(OperationSigniture("transpose", std::vector<std::string>{"matrix"}), "matrix", MatrixOperations::matrixTranspose);
    evaluator.addFunction(OperationSigniture("inverse", std::vector<std::string>{"float"}), "float", FloatOperations::doubleInverse);

    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("/", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleDivision, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("==", std::vector<std::string>{"float", "float"}), "bool", FloatOperations::doubleEqual, Properties{2, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.addOperator(OperationSigniture("*", std::vector<std::string>{"float", "matrix"}), "matrix", MatrixOperations::doubleMatrixMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.addConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    evaluator.addConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}