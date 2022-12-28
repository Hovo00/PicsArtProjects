#include "DontKnow.h"

void initializeOperationMap(OperationRegistry& registry) {
    registry.addOperator("+", MatrixOperations::matrixAddition, "+matrixmatrix", 2, 3, "leftToRight", "infix");
    registry.addOperator("-", MatrixOperations::matrixSubtraction, "-matrixmatrix", 2, 3, "leftToRight", "infix");
    registry.addOperator("*", MatrixOperations::matrixMultiplication, "*matrixmatrix", 2, 4, "leftToRight", "infix");
    registry.addOperator("/", MatrixOperations::matrixFloatDivision, "/matrixfloat", 2, 4, "leftToRight", "infix");
    registry.addOperator("==", MatrixOperations::matrixEqual, "==matrixmatrix", 2, 2, "leftToRight", "infix");
    registry.addOperator("?", BoolOperations::questionMarkBool, "?bool", 1, 1, "leftToRight", "postfix");
    registry.addOperator(":", FloatOperations::thernarfloat, ":boolfloatfloat", 3, 2, "rightToLeft", "infix");
    
    registry.addFunction("inverse", MatrixOperations::matrixInverse, "inversematrix", 1);
    registry.addFunction("sin", FloatOperations::sinus, "sinfloat", 1);
    registry.addFunction("cos", FloatOperations::cosinus, "cosfloat", 1);
    registry.addFunction("det", MatrixOperations::matrixDeterminant, "detmatrix", 1);
    registry.addFunction("select", MatrixOperations::Select, "selectmatrixmatrixmatrix", 3);
    registry.addFunction("transpose", MatrixOperations::matrixTranspose, "transposematrix", 1);

    registry.addFunctionOverload("inverse", FloatOperations::floatInverse, "inversefloat");
    registry.addOperatorOverload("+", FloatOperations::floatAddition, "+floatfloat");
    registry.addOperatorOverload("-", FloatOperations::floatSubtraction, "-floatfloat");
    registry.addOperatorOverload("/", FloatOperations::floatDivision, "/floatfloat");
    registry.addOperatorOverload("*", FloatOperations::floatMultiplication, "*floatfloat");
    registry.addOperatorOverload("==", FloatOperations::floatEqual, "==floatfloat");
    registry.addOperatorOverload("?", FloatOperations::questionMarkFloat, "?float");
    registry.addOperatorOverload("*", MatrixOperations::matrixFloatMultiplication, "*matrixfloat");
    registry.addOperatorOverload("+", MatrixOperations::matrixFloatAddition, "+matrixfloat");
    registry.addOperatorOverload("-", MatrixOperations::matrixFloatSubtraction, "-matrixfloat");
    registry.addOperatorOverload("*", MatrixOperations::floatMatrixMultiplication, "*floatmatrix");
}