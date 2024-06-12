#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/editor.h"

TEST(EditorTest, NewLineAddsLineToEmptyList) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, NewLineAddsLineToNonEmptyList) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    Editor::newLine(&content, &cmdLog, "Hello, GitHub Copilot!");
    EXPECT_STREQ(content.tail->text, "Hello, GitHub Copilot!");
    EXPECT_EQ(content.length, 2);
}

TEST(EditorTest, PrintTextOutputsCorrectly) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::printText(&content);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}

TEST(EditorTest, AppendTextToEmptyList) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::appendText(&content, &cmdLog, "Hello, World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
    EXPECT_EQ(content.length, 1);
}

TEST(EditorTest, AppendTextToNonEmptyList) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, ");
    Editor::appendText(&content, &cmdLog, "World!");
    EXPECT_STREQ(content.head->text, "Hello, World!");
}

TEST(EditorTest, SearchPatternNotFound) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is not found.\n");
}

TEST(EditorTest, SearchPatternFound) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, GitHub Copilot!");
    testing::internal::CaptureStdout();
    Editor::search(&content, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "'GitHub Copilot' is at line 0, index 7.\n");
}

TEST(EditorTest, InsertByInBounds) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    Editor::insertBy(&content, &cmdLog, 0, 7, "GitHub Copilot, ");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot, World!");
}

TEST(EditorTest, InsertByOutOfBounds) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();  // Redirect std::cin and save the old buffer
    testing::internal::CaptureStderr();
    Editor::insertBy(&content, &cmdLog, 2, 0, "GitHub Copilot, ");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);  // Restore the original buffer
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, ReplaceByValidIndex) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    Editor::replaceBy(&content, &cmdLog, 0, 7, "GitHub Copilot");
    EXPECT_STREQ(content.head->text, "Hello, GitHub Copilot");
}

TEST(EditorTest, ReplaceByInvalidLineIndex) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::replaceBy(&content, &cmdLog, 2, 7, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, ReplaceByInvalidCharIndex) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::replaceBy(&content, &cmdLog, 0, 20, "GitHub Copilot");
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Char index is out of bounds.");
}

TEST(EditorTest, DeleteByValidIndexAndLength) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    Editor::deleteBy(&content, &cmdLog, 0, 7, 5);
    EXPECT_STREQ(content.head->text, "Hello, !");
}

TEST(EditorTest, DeleteByInvalidLineIndex) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::deleteBy(&content, &cmdLog, 2, 7, 5);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(EditorTest, DeleteByInvalidCharIndex) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    Editor::deleteBy(&content, &cmdLog, 0, 20, 5);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(output, "Char index is out of bounds.");
}

TEST(EditorTest, DeleteByLengthExceedsRemainingCharacters) {
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, World!");
    Editor::deleteBy(&content, &cmdLog, 0, 7, 20);
    EXPECT_STREQ(content.head->text, "Hello, ");
}