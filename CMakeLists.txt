cmake_minimum_required(VERSION 2.4)

project(compiler)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app main.cc lexer.cc token.cc parser.cc emit.cc)