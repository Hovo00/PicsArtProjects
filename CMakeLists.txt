cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)


project(expression_evaluator LANGUAGES CXX)


add_executable(${PROJECT_NAME} main.cpp Operator.cpp  Lexer.cpp Matrix.cpp Bool.cpp
Evaluator.cpp Input.cpp Exception.cpp Operand.cpp Float.cpp MapInitialization.cpp
OperationRegistry.cpp Output.cpp ConvertFunctions.cpp FloatOperations.cpp
MatrixOperations.cpp TypeConversionFunctions.cpp OperationInfo.cpp OperandValidators.cpp
CreatorFunctions.cpp)



function(print var)
  message("${var} = ${${var}}")
endfunction()

print(PROJECT_NAME)
message(projik)
