#include "gtest/gtest.h"
#include "../include/buffer.h"
#include "../include/editor.h"

TEST(BufferTest, CutRemovesTextFromContent) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, world!");
    buffer.cut(&content, &cmdLog,0, 0, 5);
    EXPECT_STREQ(content.head->text, ", world!");
    EXPECT_STREQ(buffer.getClip(), "Hello");
}

TEST(BufferTest, CopyDoesNotRemoveTextFromContent) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, world!");
    buffer.copy(&content, 0, 0, 5);
    EXPECT_STREQ(content.head->text, "Hello, world!");
    EXPECT_STREQ(buffer.getClip(), "Hello");
}

TEST(BufferTest, CopyLengthGreaterThanLineLength) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog,"Hello, world!");
    buffer.copy(&content, 0, 0, 100);
    EXPECT_STREQ(buffer.getClip(), "Hello, world!");
}

TEST(BufferTest, CopyAfterCopy) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog,"Hello, world!");
    buffer.copy(&content, 0, 0, 5);
    EXPECT_STREQ(buffer.getClip(), "Hello");
    buffer.copy(&content, 0, 7, 5);
    EXPECT_STREQ(buffer.getClip(), "world");
}

TEST(BufferTest, PasteInsertsTextFromBufferToContent) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog,"Hello, world!");
    buffer.copy(&content, 0, 0, 5);
    buffer.paste(&content, &cmdLog, 0, 6);
    EXPECT_STREQ(content.head->text, "Hello,Hello world!");
}

TEST(BufferTest, PasteDoesNothingWhenBufferIsEmpty) {
    Buffer buffer;
    LinkedList content;
    CommandsLog cmdLog;
    Editor::newLine(&content, &cmdLog, "Hello, world!");
    buffer.paste(&content, &cmdLog, 0, 6);
    EXPECT_STREQ(content.head->text, "Hello, world!");
}
