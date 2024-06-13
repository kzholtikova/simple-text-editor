#include <gtest/gtest.h>
#include "../include/cursor.h"
#include "../include/editor.h"
#include "../include/main_test.h"

TEST(CursorTest, GetCursorLineReturnsCorrectLine) {
    Line* line = new Line();
    Cursor cursor = Cursor();
    cursor.updateCursor(line, 0, 0);
    EXPECT_EQ(cursor.getCursorLine(), line);
}

TEST(CursorTest, CursorMovesWithTheTail) {
    LinkedList content;
    CommandsLog cmdLog;
    Cursor cursor = Cursor();
    Editor::newLine(&content, &cmdLog, "test0");
    cursor.updateCursor(content.tail, content.length - 1, 0);
    EXPECT_EQ(cursor.getCursorLine(), content.tail);
    Editor::newLine(&content, &cmdLog, "test1");
    cursor.updateCursor(content.tail, content.length - 1, 0);
    EXPECT_EQ(cursor.getCursorLine(), content.tail);
}

TEST(CursorTest, SetCursorUpdatesLineAndIndexes) {
    LinkedList content;
    CommandsLog cmdLog;
    Cursor cursor = Cursor();
    Editor::newLine(&content, &cmdLog, "test0");
    Editor::newLine(&content, &cmdLog, "test1");
    cursor.setCursor(&content, 1, 3);
    EXPECT_EQ(cursor.getCursorLine(), content.head->next);
    EXPECT_EQ(cursor.getCursorLineIndex(), 1);
    EXPECT_EQ(cursor.getCursorCharIndex(), 3);
}

TEST(CursorTest, SetCursorDoesNotUpdateWhenLineIndexOutOfBounds) {
    LinkedList content = LinkedList();
    Cursor cursor = Cursor();
    EXPECT_EQ(cursor.getCursorLine(), nullptr);
    EXPECT_EQ(cursor.getCursorLineIndex(), 0);
    EXPECT_EQ(cursor.getCursorCharIndex(), 0);
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    cursor.setCursor(&content, 2, 0);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(cursor.getCursorLine(), nullptr);
    EXPECT_EQ(cursor.getCursorLineIndex(), 0);
    EXPECT_EQ(cursor.getCursorCharIndex(), 0);
    EXPECT_EQ(output, "Line index is out of bounds.");
}

TEST(CursorTest, SetCursorDoesNotUpdateWhenCharIndexOutOfBounds) {
    LinkedList content = LinkedList();
    CommandsLog cmdLog;
    Cursor cursor = Cursor();
    Editor::newLine(&content, &cmdLog, "test");
    EXPECT_EQ(cursor.getCursorLine(), nullptr);
    EXPECT_EQ(cursor.getCursorLineIndex(), 0);
    EXPECT_EQ(cursor.getCursorCharIndex(), 0);
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    cursor.setCursor(&content, 0, 5);
    std::string output = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(cursor.getCursorLine(), nullptr);
    EXPECT_EQ(cursor.getCursorLineIndex(), 0);
    EXPECT_EQ(cursor.getCursorCharIndex(), 0);
    EXPECT_EQ(output, "Char index is out of bounds.");
}

TEST(CursorTest, MoveCursorRight) {
    Cursor cursor;
    Line line;
    line.text = new char[6];
    strcpy(line.text, "Hello");
    cursor.updateCursor(&line, 0, 0);

    cursor.moveCursorRight(3);
    EXPECT_EQ(cursor.getCursorCharIndex(), 3);

    cursor.moveCursorRight(3);
    EXPECT_EQ(cursor.getCursorCharIndex(), 5);
}

TEST(CursorTest, MoveCursorLeft) {
    Cursor cursor;
    Line line;
    line.text = new char[6];
    strcpy(line.text, "Hello");
    cursor.updateCursor(&line, 0, 5);

    cursor.moveCursorLeft(3);
    EXPECT_EQ(cursor.getCursorCharIndex(), 2);

    cursor.moveCursorLeft(3);
    EXPECT_EQ(cursor.getCursorCharIndex(), 0);
}
