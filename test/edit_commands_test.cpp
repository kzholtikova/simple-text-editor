#include <gtest/gtest.h>
#include "../include/edit_commands.h"

TEST(EditorTest, NewLineAddsLineToEmptyList) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, NewLineAddsLineToNonEmptyList) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::newLine(&content, "Hello, GitHub Copilot!");
    EXPECT_STREQ(content.tail->text, "Hello, GitHub Copilot!");
    EXPECT_EQ(content.length, 2);
}

TEST(EditorTest, PrintTextOutputsCorrectly) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::printText(&content);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}

TEST(EditorTest, AppendTextToEmptyList) {
    LinkedList content;
    Editor::appendText(&content, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, AppendTextToNonEmptyList) {
    LinkedList content;
    Editor::newLine(&content, "Hello, ");
    Editor::appendText(&content, "World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
}

TEST(EditorTest, InsertByOutOfBounds) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    testing::internal::CaptureStderr();
    Editor::insertBy(&content, 2, 0, "GitHub Copilot, ");
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Line index out of bounds.\n");
}

TEST(EditorTest, InsertByInBounds) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::insertBy(&content, 0, 7, "GitHub Copilot, ");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot, World!");
}

TEST(EditorTest, SearchPatternNotFound) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    testing::internal::CaptureStderr();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "'GitHub Copilot' is not found\n");
}

TEST(EditorTest, SearchPatternFound) {
    LinkedList content;
    Editor::newLine(&content, "Hello, GitHub Copilot!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot'found at line 0, index 7\n");
}
