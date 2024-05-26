cmake_minimum_required(VERSION 3.28)
project(simple_text_editor C CXX)

set(CMAKE_C_STANDARD 11)

# Main application target
add_executable(simple_text_editor src/main.cpp
        src/parser.cpp
        src/text_storage.cpp
        src/edit_commands.cpp
        src/file_commands.cpp
        include/file_commands.h
        src/additional_commands.cpp
        include/additional_commands.h
)

# Add Google Test to the project
add_subdirectory(cmake-build-debug/googletest)

# Test target
add_executable(simple_text_editor_tests test/main_test.cpp include/main_test.h
        test/text_storage_test.cpp src/text_storage.cpp
        test/edit_commands_test.cpp src/edit_commands.cpp src/parser.cpp
        test/file_commands_test.cpp src/file_commands.cpp)

# Link Google Test to the test target
target_link_libraries(simple_text_editor_tests gtest_main)
