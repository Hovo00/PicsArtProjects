cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(expression_evaluator LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp InputClass.cpp Token.cpp Operator.cpp
 Matrix.cpp Lexer.cpp Parser.cpp Node.cpp Tree.cpp TypeInfo.cpp)



function(print var)
  message("${var} = ${${var}}")
endfunction()

print(PROJECT_NAME)
message(projik)
