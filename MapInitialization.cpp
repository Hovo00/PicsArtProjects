#include "MapInitialization.hpp"

void initEvaluatorOperationMap(Evaluator& evaluator) {
    evaluator.registerOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "matrix"}), "matrix", MatrixOperations::matrixMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("/", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatDivision, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("==", std::vector<std::string>{"matrix", "matrix"}), "bool", MatrixOperations::matrixEqual, Properties{2, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("?:", std::vector<std::string>{"bool", "float", "float"}), "float", FloatOperations::thernardouble, Properties{1, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("[|]", std::vector<std::string>{"bool", "float", "float", "float"}), "float", FloatOperations::fornarydouble, Properties{0, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerFunction(OperationSigniture("inverse", std::vector<std::string>{"matrix"}), "matrix",  MatrixOperations::matrixInverse);
    evaluator.registerFunction(OperationSigniture("sin", std::vector<std::string>{"float"}), "float", FloatOperations::sinus);
    evaluator.registerFunction(OperationSigniture("cos", std::vector<std::string>{"float"}), "float", FloatOperations::cosinus);
    evaluator.registerFunction(OperationSigniture("det", std::vector<std::string>{"matrix"}), "float", MatrixOperations::matrixDeterminant);
    evaluator.registerFunction(OperationSigniture("select", std::vector<std::string>{"matrix", "matrix", "matrix"}), "matrix", MatrixOperations::Select);
    evaluator.registerFunction(OperationSigniture("transpose", std::vector<std::string>{"matrix"}), "matrix", MatrixOperations::matrixTranspose);
    evaluator.registerFunction(OperationSigniture("inverse", std::vector<std::string>{"float"}), "float", FloatOperations::doubleInverse);

    evaluator.registerOperator(OperationSigniture("+", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("-", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("/", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleDivision, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("*", std::vector<std::string>{"float", "float"}), "float", FloatOperations::doubleMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("==", std::vector<std::string>{"float", "float"}), "bool", FloatOperations::doubleEqual, Properties{2, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("*", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("+", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatAddition, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("-", std::vector<std::string>{"matrix", "float"}), "matrix", MatrixOperations::matrixFloatSubtraction, Properties{3, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerOperator(OperationSigniture("*", std::vector<std::string>{"float", "matrix"}), "matrix", MatrixOperations::doubleMatrixMultiplication, Properties{4, Associativity::LeftToRight, Notation::Infix});
    evaluator.registerConversion("bool", "float", TypeConversionFunctions::boolToFloat);
    evaluator.registerConversion("float", "bool", TypeConversionFunctions::FloatToBool);
}