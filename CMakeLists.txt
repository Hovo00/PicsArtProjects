cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(expression_evaluator LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp Expression.cpp Operator.cpp  Matrix.cpp 
ExpressionTree.cpp TypeInfo.cpp Lexer.cpp InputClass.cpp Exception.cpp Operand.cpp Float.cpp 
OperationRegistry.cpp)



function(print var)
  message("${var} = ${${var}}")
endfunction()

print(PROJECT_NAME)
message(projik)
