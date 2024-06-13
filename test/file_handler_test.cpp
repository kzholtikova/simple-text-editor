#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/file_handler.h"
#include "../include/editor.h"

TEST(FileHandlerTest, SaveAndLoadEmptyFile) {
    LinkedList content;
    std::streambuf* coutbuf = redirectCout();
    FileHandler::saveToFile(&content, "empty.txt");
    LinkedList loadedContent;
    FileHandler::loadFromFile(&loadedContent, nullptr, "empty.txt");
    resetCout(coutbuf);
    EXPECT_EQ(loadedContent.length, 0);
    EXPECT_EQ(loadedContent.head, nullptr);
}

TEST(FileHandlerTest, SaveAndLoadFile) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, World!");
    std::streambuf* coutbuf = redirectCout();
    FileHandler::saveToFile(&content, "hello.txt");
    LinkedList loadedContent;
    FileHandler::loadFromFile(&loadedContent, nullptr, "hello.txt");
    resetCout(coutbuf);
    EXPECT_STREQ(loadedContent.head->text, content.head->text);
}
