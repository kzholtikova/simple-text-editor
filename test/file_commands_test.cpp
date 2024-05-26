#include <gtest/gtest.h>
#include "../include/main_test.h"
#include "../include/file_commands.h"

class FileCommandsTest : public CommandsTest {};

TEST_F(FileCommandsTest, OpenFileWithValidMode) {
    setInput("testFile.txt");
    redirectStdout();
    FILE* file = openFile("w");
    resetStdout();

    ASSERT_NE(file, nullptr);
    fclose(file);
}

TEST_F(FileCommandsTest, OpenFileWithInvalidMode) {
    setInput("testFile.txt");
    redirectStdout();
    FILE* file = openFile("invalid_mode");
    resetStdout();

    ASSERT_EQ(file, nullptr);
}

TEST_F(FileCommandsTest, SaveToFile) {
    // Add some lines to the list
    list->head = createLine("Line 1");
    list->tail = list->head;
    list->tail->next = createLine("Line 2");
    list->tail = list->tail->next;
    list->length = 2;

    setInput("testFile.txt");
    redirectStdout();
    saveToFile(list);
    resetStdout();

    // Open the file and check its contents
    FILE* file = fopen("testFile.txt", "r");
    char line[100];
    fgets(line, 100, file);
    ASSERT_STREQ(line, "Line 1\n");
    fgets(line, 100, file);
    ASSERT_STREQ(line, "Line 2\n");
    fclose(file);
}

TEST_F(FileCommandsTest, LoadFromFileToEmptyList) {
    setInput("testFile.txt");
    redirectStdout();
    loadFromFile(list);
    resetStdout();

    ASSERT_EQ(list->length, 2);
    ASSERT_STREQ(list->head->text, "Line 1");
    ASSERT_STREQ(list->head->next->text, "Line 2");
}

TEST_F(FileCommandsTest, LoadFromFileToNonEmptyList) {
    list->head = createLine("Line 1");
    list->tail = list->head;
    list->tail->next = createLine("Line 2");
    list->tail = list->tail->next;
    list->length = 2;

    setInput("testFile.txt");
    redirectStdout();
    loadFromFile(list);
    resetStdout();

    ASSERT_EQ(list->length, 4);
    ASSERT_STREQ(list->head->text, "Line 1");
    ASSERT_STREQ(list->head->next->text, "Line 2");
    ASSERT_STREQ(list->head->next->next->text, "Line 1");
    ASSERT_STREQ(list->head->next->next->next->text, "Line 2");
}
