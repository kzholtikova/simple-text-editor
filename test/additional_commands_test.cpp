#include <gtest/gtest.h>
#include "../include/additional_commands.h"
#include "../include/main_test.h"

class AdditionalCommandsTest : public CommandsTest {}; // searches for 'test pattern'

TEST(AdditionalCommandsTest, ClearConsole) {
    EXPECT_NO_THROW(clearConsole());
}

TEST(AdditionalCommandsTest, SearchInSingleLineWithResult) {
    LinkedList list;
    Line line;
    line.text = "This is a test pattern";
    line.next = NULL;
    list.head = &line;

    setInput("test pattern");
    redirectStdout();
    std::string output = captureStdout(search, &list);
    resetStdout();
    EXPECT_EQ("'test pattern' found at line 0, index 10\n", output.substr(output.find(":") + 2));
}

TEST(AdditionalCommandsTest, SearchInSingleLineWithoutResult) {
    LinkedList list;
    Line line;
    line.text = "This is a different pattern";
    line.next = NULL;
    list.head = &line;

    setInput("test pattern");
    redirectStdout();
    std::string output = captureStdout(search, &list);
    resetStdout();
    EXPECT_EQ("'test pattern' is not found\n", output.substr(output.find(":") + 2));
}

TEST(AdditionalCommandsTest, SearchInMultipleLines) {
    LinkedList list;
    Line line1, line2;
    line1.text = "This is a test pattern";
    line1.next = &line2;
    line2.text = "Another test pattern here";
    line2.next = NULL;
    list.head = &line1;

    setInput("test pattern");
    redirectStdout();
    std::string output = captureStdout(search, &list);
    resetStdout();
    EXPECT_EQ("'test pattern' found at line 0, index 10\n'test pattern' found at line 1, index 8\n", output.substr(output.find(":") + 2));
}

TEST(AdditionalCommandsTest, SearchInEmptyList) {
    LinkedList list;
    list.head = NULL;

    setInput("test pattern");
    redirectStdout();
    std::string output = captureStdout(search, &list);
    resetStdout();
    EXPECT_EQ("'test pattern' is not found\n", output.substr(output.find(":") + 2));
}

TEST(AdditionalCommandsTest, SearchOverflownPattern) {
    LinkedList list;
    Line line;
    line.text = "Short";
    line.next = NULL;
    list.head = &line;

    setInput("test pattern");
    redirectStdout();
    std::string output = captureStdout(search, &list);
    resetStdout();
    EXPECT_EQ("'test pattern' is not found\n", output.substr(output.find(":") + 2));
}