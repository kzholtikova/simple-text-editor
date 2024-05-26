#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/edit_commands.h"

class EditCommandsTest : public CommandsTest {};

TEST_F(EditCommandsTest, NewLineToEmptyList) {
    setInput("Hello, world!\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    ASSERT_EQ(list->length, 1);
    ASSERT_NE(list->head, nullptr);
    ASSERT_STREQ(list->head->text, "Hello, world!");
}

TEST_F(EditCommandsTest, NewLineToNonEmptyList) {
    list->head = createLine("Existing line");
    list->tail = list->head;
    list->length = 1;

    setInput("New line\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    ASSERT_EQ(list->length, 2);
    ASSERT_NE(list->tail, nullptr);
    ASSERT_STREQ(list->tail->text, "New line");
}

TEST_F(EditCommandsTest, AppendTextToEmptyList) {
    setInput("Hello World!\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    ASSERT_EQ(list->length, 1);
    ASSERT_NE(list->head, nullptr);
    ASSERT_STREQ(list->head->text, "Hello World!");
}

TEST_F(EditCommandsTest, AppendTextToNonEmptyList) {
    setInput("Hello\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    setInput(" World!\n");
    redirectStdout();
    appendText(list);
    resetStdout();

    ASSERT_EQ(list->length, 1);
    ASSERT_NE(list->head, nullptr);
    ASSERT_STREQ(list->head->text, "Hello World!");
}

TEST_F(EditCommandsTest, InsertByCorrectPosition) {
    setInput("Line 1\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    setInput("Line 2\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    setInput("0\n5\nInserted Text\n");
    redirectStdout();
    insertBy(list);
    resetStdout();

    ASSERT_EQ(list->length, 2);
    ASSERT_NE(list->head, nullptr);
    ASSERT_STREQ(list->head->text, "Line Inserted Text1");
    ASSERT_NE(list->head->next, nullptr);
    ASSERT_STREQ(list->head->next->text, "Line 2");
}

TEST_F(EditCommandsTest, InsertByToEmptyList) {
    setInput("0\n5\nInserted Text\n");
    redirectStdout();
    insertBy(list);
    resetStdout();

    ASSERT_EQ(list->length, 0);
}

TEST_F(EditCommandsTest, PrintText) {
    setInput("Line 1\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    setInput("Line 2\n");
    redirectStdout();
    newLine(list);
    resetStdout();

    std::string output = captureStdout(printText, list);
    std::string expectedOutput = "Line 1\nLine 2\n";
    ASSERT_EQ(output, expectedOutput);
}
