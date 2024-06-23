cmake_minimum_required(VERSION 3.28)
project(simple_text_editor C CXX)

set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(include)

# Add the shared library
add_library(caesar_cipher SHARED src/caesar_cipher.cpp)

# Main application target
add_executable(simple_text_editor src/main.cpp
        src/parser.cpp
        src/text_storage.cpp
        src/editor.cpp
        src/file_handler.cpp
        src/application.cpp
        src/buffer.cpp
        src/commands_log.cpp
        src/cursor.cpp
        src/caesar_cipher.cpp
)

# Link the caesar_cipher library to the simple_text_editor target
target_link_libraries(simple_text_editor caesar_cipher dl)

# Add Google Test to the project
add_subdirectory(cmake-build-debug/googletest)

# Test target
add_executable(simple_text_editor_tests test/main_test.cpp include/main_test.h
        test/text_storage_test.cpp
        src/text_storage.cpp
        test/parser_test.cpp
        src/parser.cpp
        test/editor_test.cpp
        src/editor.cpp
        test/file_handler_test.cpp
        src/file_handler.cpp
        test/buffer_test.cpp
        src/buffer.cpp
        test/commands_log_test.cpp
        src/commands_log.cpp
        test/cursor_test.cpp src/cursor.cpp
        src/application.cpp
        test/caesar_cipher_test.cpp src/caesar_cipher.cpp
)

# Link Google Test to the test target
target_link_libraries(simple_text_editor_tests gtest_main caesar_cipher)