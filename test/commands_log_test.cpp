#include <gtest/gtest.h>
#include "../include/commands_log.h"

TEST(CommandsLogTest, LogBeforeIncreasesStackSizeWhenFull) {
    LinkedList content;
    CommandsLog cmdLog(content);
    Line line("test");
    for (int i = 0; i < 4; i++) {
        cmdLog.logBefore(line, i);
    }
    cmdLog.logBefore(line, 4);
    SUCCEED();
}

TEST(CommandsLogTest, LogBeforeAndAfterMaintainCorrectOrder) {
    LinkedList content;
    CommandsLog cmdLog(content);
    Line line1("test1");
    Line line2("test2");
    cmdLog.logBefore(line1, 0);
    cmdLog.logAfter(line1);
    cmdLog.logBefore(line2, 1);
    cmdLog.logAfter(line2);
    EXPECT_STREQ(cmdLog.getLineBefore(0).text, "test1");
    EXPECT_STREQ(cmdLog.getLineAfter(0).text, "test1");
    EXPECT_STREQ(cmdLog.getLineBefore(1).text, "test2");
    EXPECT_STREQ(cmdLog.getLineAfter(1).text, "test2");
}

TEST(CommandsLogTest, UndoAndRedoCorrectlyModifyContent) {
    LinkedList content;
    CommandsLog cmdLog(content);
    Line line1("test1");
    Line line2("test2");
    cmdLog.logBefore(line1, 0);
    cmdLog.logAfter(line1);
    cmdLog.logBefore(line2, 1);
    cmdLog.logAfter(line2);
    cmdLog.undo();
    EXPECT_STREQ(content.head->text, "test1");
    cmdLog.redo();
    EXPECT_STREQ(content.head->text, "test2");
}

TEST(CommandsLogTest, UndoAndRedoDoNothingWhenEmpty) {
    LinkedList content;
    CommandsLog cmdLog(content);
    cmdLog.undo();
    EXPECT_EQ(content.head, nullptr);
    cmdLog.redo();
    EXPECT_EQ(content.head, nullptr);
}
