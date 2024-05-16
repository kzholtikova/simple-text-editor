cmake_minimum_required(VERSION 3.28)
project(simple_text_editor C CXX)

set(CMAKE_C_STANDARD 11)

add_executable(simple_text_editor src/main.cpp
        src/parser..cpp
)
