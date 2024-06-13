#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/editor.h"

TEST(EditorTest, NewLineAddsLineToEmptyList) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, NewLineAddsLineToNonEmptyList) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, World!");
    Editor::newLine(&content, nullptr, "Hello, GitHub Copilot!");
    EXPECT_STREQ(content.tail->text, "Hello, GitHub Copilot!");
    EXPECT_EQ(content.length, 2);
}

TEST(EditorTest, PrintTextOutputsCorrectly) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::printText(&content);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}

TEST(EditorTest, AppendTextToEmptyList) {
    LinkedList content;
    Editor::appendText(&content, nullptr, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, AppendTextToNonEmptyList) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, ");
    Editor::appendText(&content, nullptr, "World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
}

TEST(EditorTest, SearchPatternNotFound) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is not found.\n");
}

TEST(EditorTest, SearchPatternFound) {
    LinkedList content;
    Editor::newLine(&content, nullptr, "Hello, GitHub Copilot!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is at line 0, index 7.\n");
}

TEST(EditorTest, InsertByInBounds) {
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, World!");
    c.setCursor(&content, 0, 7);
    Editor::insertText(nullptr, c, "GitHub Copilot, ");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot, World!");
}

TEST(EditorTest, ReplaceByValidIndex) {
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, World!");
    c.setCursor(&content, 0, 7);
    Editor::replaceText(nullptr, c, "GitHub Copilot");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot");
}

TEST(EditorTest, DeleteByValidIndexAndLength) {
    LinkedList content;
    CommandsLog cmdLog;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, World!");
    c.setCursor(&content, 0, 7);
    Editor::deleteText(nullptr, c, 5);
    EXPECT_STREQ(content.head->text, "Hello, !");
}

TEST(EditorTest, DeleteByLengthExceedsRemainingCharacters) {
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, World!");
    c.setCursor(&content, 0, 7);
    Editor::deleteText(nullptr, c, 20);
    EXPECT_STREQ(content.head->text, "Hello, ");
}