#include <gtest/gtest.h>
#include "../include/main_test.h"
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

TEST(EditorTest, SearchPatternNotFound) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is not found.\n");
}

TEST(EditorTest, SearchPatternFound) {
    LinkedList content;
    Editor::newLine(&content, "Hello, GitHub Copilot!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is at line 0, index 7.\n");
}

TEST(EditorTest, InsertByInBounds) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::insertBy(&content, 0, 7, "GitHub Copilot, ");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot, World!");
}

TEST(EditorTest, InsertByOutOfBounds) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();  // Redirect std::cin and save the old buffer
    testing::internal::CaptureStderr();
    Editor::insertBy(&content, 2, 0, "GitHub Copilot, ");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);  // Restore the original buffer
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, ReplaceByValidIndex) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::replaceBy(&content, 0, 7, "GitHub Copilot");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot");
}

TEST(EditorTest, ReplaceByInvalidLineIndex) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::replaceBy(&content, 2, 7, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, ReplaceByInvalidCharIndex) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::replaceBy(&content, 0, 20, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Char index is out of bounds.");
}

TEST(EditorTest, DeleteByValidIndexAndLength) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::deleteBy(&content, 0, 7, 5);
    EXPECT_STREQ(content.head->text, "Hello, !");
}

TEST(EditorTest, DeleteByInvalidLineIndex) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::deleteBy(&content, 2, 7, 5);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, DeleteByInvalidCharIndex) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::deleteBy(&content, 0, 20, 5);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Char index is out of bounds.");
}

TEST(EditorTest, DeleteByLengthExceedsRemainingCharacters) {
    LinkedList content;
    Editor::newLine(&content, "Hello, World!");
    Editor::deleteBy(&content, 0, 7, 20);
    EXPECT_STREQ(content.head->text, "Hello, ");
}