#include <gtest/gtest.h>
#include "../include/commands_log.h"
#include "../include/editor.h"
#include "../include/main_test.h"

TEST(CommandsLogTest, LogBeforeIncreasesStackSizeWhenFull) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    try {
        for (int i = 0; i < 6; i++) {
            Editor::newLine(&content, &cmdLog,"test");
        }
        SUCCEED();
    } catch (const std::exception& e) {
        FAIL();
    }
}

TEST(CommandsLogTest, LogBeforeAndAfterMaintainCorrectOrder) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Editor::newLine(&content, &cmdLog, "test1");
    Editor::newLine(&content, &cmdLog, "test2");
    EXPECT_EQ(cmdLog.getLineLog(0).before.text, nullptr);
    EXPECT_STREQ(cmdLog.getLineLog(0).after.text, "test1");
    EXPECT_EQ(cmdLog.getLineLog(1).before.text, nullptr);
    EXPECT_STREQ(cmdLog.getLineLog(1).after.text, "test2");
}

TEST(CommandsLogTest, UndoAndRedoNewLine) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Editor::newLine(&content, &cmdLog, "test1");
    Editor::newLine(&content, &cmdLog, "test2");
    cmdLog.undo(&content);
    EXPECT_EQ(content.length, 1);
    EXPECT_STREQ(content.tail->text, "test1");
    cmdLog.redo(&content);
    EXPECT_EQ(content.length, 2);
    EXPECT_STREQ(content.tail->text, "test2");
}

TEST(CommandsLogTest, UndoAndRedoModifyContent) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    Editor::appendText(&content, &cmdLog, "test1");
    Editor::insertBy(&content, &cmdLog, 0, 0, "test2");
    cmdLog.undo(&content);
    EXPECT_STREQ(content.head->text, "test1");
    cmdLog.redo(&content);
    EXPECT_STREQ(content.head->text, "test2test1");
    EXPECT_EQ(content.length, 1);
}

TEST(CommandsLogTest, UndoAndRedoDoNothingWhenEmpty) {
    LinkedList content;
    CommandsLog cmdLog = CommandsLog();
    std::streambuf* coutbuf = redirectCout();
    cmdLog.undo(&content);
    resetCout(coutbuf);
    EXPECT_EQ(content.head, nullptr);
    coutbuf = redirectCout();
    cmdLog.redo(&content);
    resetCout(coutbuf);
    EXPECT_EQ(content.head, nullptr);
}
