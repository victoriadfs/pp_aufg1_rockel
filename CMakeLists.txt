cmake_minimum_required(VERSION 3.20)

project(aufgabe1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Werror -Wextra")
set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 20)


include_directories(include)
include_directories(external)

add_executable(base_test examples/main.cpp src/SAT.cpp
    src/klausel.cpp
    src/variable.cpp
    src/DIMACS_einlesen.cpp
    src/backtracking.cpp
    src/wahrheitsbelegung.cpp
    src/belegung_wahr.cpp)
    
add_executable(opt_test examples/main.cpp src/SAT.cpp
    src/klausel.cpp
    src/variable.cpp
    src/DIMACS_einlesen.cpp
    src/backtracking.cpp
    src/wahrheitsbelegung.cpp
    src/belegung_wahr.cpp)

add_executable(san_test examples/main.cpp src/SAT.cpp
    src/klausel.cpp
    src/variable.cpp
    src/DIMACS_einlesen.cpp
    src/backtracking.cpp
    src/wahrheitsbelegung.cpp
    src/belegung_wahr.cpp)

target_compile_options(san_test PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(san_test PRIVATE -fsanitize=address -fsanitize=undefined)

target_compile_options(opt_test PRIVATE -O3)
target_compile_options(base_test PRIVATE -g -fno-omit-frame-pointer)

configure_file(files/test1.txt files/output.txt)
