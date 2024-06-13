cmake_minimum_required(VERSION 3.28)
project(simple_text_editor C CXX)

set(CMAKE_C_STANDARD 11)

# Main application target
add_executable(simple_text_editor src/main.cpp
        src/parser.cpp include/parser.h
        src/text_storage.cpp include/text_storage.h
        src/editor.cpp include/editor.h
        src/file_handler.cpp include/file_handler.h
        src/application.cpp include/application.h
        src/buffer.cpp include/buffer.h
        src/commands_log.cpp include/commands_log.h
        src/cursor.cpp include/cursor.h
)

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
)

# Link Google Test to the test target
target_link_libraries(simple_text_editor_tests gtest_main)
