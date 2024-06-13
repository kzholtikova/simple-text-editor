#include <gtest/gtest.h>
#include "../include/commands_log.h"
#include "../include/editor.h"
#include "../include/main_test.h"

TEST(CommandsLogTest, LogBeforeIncreasesStackSizeWhenFull) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    for (int i = 0; i < 6; i++) {
        Editor::newLine(&content, &cmdLog,"test");
    }
}

TEST(CommandsLogTest, LogBeforeAndAfterMaintainCorrectOrder) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Editor::newLine(&content, &cmdLog, "test1");
    Editor::newLine(&content, &cmdLog, "test2");
    EXPECT_EQ(cmdLog.getLineLog(0).before, nullptr);
    EXPECT_STREQ(cmdLog.getLineLog(0).after, "test1");
    EXPECT_EQ(cmdLog.getLineLog(1).before, nullptr);
    EXPECT_STREQ(cmdLog.getLineLog(1).after, "test2");
}

TEST(CommandsLogTest, UndoAndRedoNewLine) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Cursor c;
    Editor::newLine(&content, &cmdLog, "test1");
    Editor::newLine(&content, &cmdLog, "test2");
    c.updateCursor(content.tail, content.length - 1, 0);
    cmdLog.undo(&content, c);
    EXPECT_EQ(content.length, 1);
    EXPECT_STREQ(content.tail->text, "test1");
    cmdLog.redo(&content, c);
    EXPECT_EQ(content.length, 2);
    EXPECT_STREQ(content.tail->text, "test2");
}

TEST(CommandsLogTest, UndoAndRedoModifyContent) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Cursor c = Cursor();
    Editor::appendText(&content, &cmdLog, "test1");
    c.updateCursor(content.tail, content.length - 1, 0);
    Editor::insertText(&cmdLog, c, "test2");
    cmdLog.undo(&content, c);
    EXPECT_STREQ(content.head->text, "test1");
    cmdLog.redo(&content, c);
    EXPECT_STREQ(content.head->text, "test2test1");
    EXPECT_EQ(content.length, 1);
}

TEST(CommandsLogTest, UndoAndRedoDoNothingWhenEmpty) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Cursor c;
    std::streambuf* coutbuf = redirectCout();
    cmdLog.undo(&content, c);
    resetCout(coutbuf);
    EXPECT_EQ(content.head, nullptr);
    coutbuf = redirectCout();
    cmdLog.redo(&content, c);
    resetCout(coutbuf);
    EXPECT_EQ(content.head, nullptr);
}
