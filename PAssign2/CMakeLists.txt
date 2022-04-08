cmake_minimum_required(VERSION 3.21)
project(BankersAlgo)
#eigen now supports C++17
set(CMAKE_CXX_STANDARD 17)

#for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(BankersAlgo
    src/main.cpp
    src/file.cpp
    src/staffer.cpp
    src/banker.h
  )
