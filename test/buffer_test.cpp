#include "gtest/gtest.h"
#include "../include/buffer.h"
#include "../include/editor.h"

TEST(BufferTest, CutRemovesTextFromContent) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, world!");
    c.updateCursor(content.tail, content.length - 1, 0);
    buffer.cut(nullptr, c, 5);
    EXPECT_STREQ(content.head->text, ", world!");
    EXPECT_STREQ(buffer.getClip(), "Hello");
}

TEST(BufferTest, CopyDoesNotRemoveTextFromContent) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, world!");
    c.updateCursor(content.tail, content.length - 1, 0);
    buffer.copy(c, 5);
    EXPECT_STREQ(content.head->text, "Hello, world!");
    EXPECT_STREQ(buffer.getClip(), "Hello");
}

TEST(BufferTest, CopyLengthGreaterThanLineLength) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr,"Hello, world!");
    c.updateCursor(content.tail, content.length - 1, 0);
    buffer.copy(c, 100);
    EXPECT_STREQ(buffer.getClip(), "Hello, world!");
}

TEST(BufferTest, CopyAfterCopy) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr,"Hello, world!");
    c.updateCursor(content.tail, content.length - 1, 0);
    buffer.copy(c, 5);
    EXPECT_STREQ(buffer.getClip(), "Hello");
    c.setCursor(&content, 0, 7);
    buffer.copy(c, 5);
    EXPECT_STREQ(buffer.getClip(), "world");
}

TEST(BufferTest, PasteInsertsTextFromBufferToContent) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr,"Hello, world!");
    c.updateCursor(content.tail, content.length - 1, 0);
    buffer.copy(c, 5);
    c.setCursor(&content, 0, 6);
    buffer.paste(nullptr, c);
    EXPECT_STREQ(content.head->text, "Hello,Hello world!");
}

TEST(BufferTest, PasteDoesNothingWhenBufferIsEmpty) {
    Buffer buffer;
    LinkedList content;
    Cursor c = Cursor();
    Editor::newLine(&content, nullptr, "Hello, world!");
    c.setCursor(&content, 0, 6);
    buffer.paste(nullptr, c);
    EXPECT_STREQ(content.head->text, "Hello, world!");
}
