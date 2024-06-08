#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/file_commands.h"
#include "../include/edit_commands.h"

TEST(FileHandlerTest, SaveToFileWithEmptyContent) {
    LinkedList content;
    std::streambuf* coutbuf = redirectCout();
    FileHandler::saveToFile(&content, "empty.txt");
    resetCout(coutbuf);
}

TEST(FileHandlerTest, SaveToFileWithContent) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* coutbuf = redirectCout();
    FileHandler::saveToFile(&content, "test.txt");
    resetCout(coutbuf);
}

TEST(FileHandlerTest, LoadFromFileWithEmptyFile) {
    LinkedList content;
    std::streambuf* coutbuf = redirectCout();
    FileHandler::loadFromFile(&content, "empty.txt");
    resetCout(coutbuf);
    EXPECT_EQ(content.length, 0);
}

TEST(FileHandlerTest, LoadFromFileWithContent) {
    LinkedList content;
    std::streambuf* coutbuf = redirectCout();
    FileHandler::loadFromFile(&content, "test.txt");
    resetCout(coutbuf);
}

TEST(FileHandlerTest, SaveAndLoadFile) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* coutbuf = redirectCout();
    FileHandler::saveToFile(&content, "hello.txt");
    LinkedList loadedContent;
    FileHandler::loadFromFile(&loadedContent, "hello.txt");
    resetCout(coutbuf);
}
