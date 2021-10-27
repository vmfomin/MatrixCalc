cmake_minimum_required(VERSION 3.17)
project(MatixCalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -pedantic-errors -Wall -Wextra -Wpedantic")

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(MatixCalc main.cpp ${HEADERS} ${SOURCES})