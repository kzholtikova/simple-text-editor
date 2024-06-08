#include <gtest/gtest.h>
#include "../include/parser.h"

TEST(ParserTest, ReadTextReturnsCorrectText) {
    testing::internal::CaptureStdout();
    std::string input = "Hello, World!\n";
    std::istringstream ss(input);
    std::cin.rdbuf(ss.rdbuf());
    char* text = Parser::readText();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(text, "Hello, World!");
    free(text);
}

TEST(ParserTest, ReadTextHandlesEmptyInput) {
    testing::internal::CaptureStdout();
    std::string input = "\n";
    std::istringstream ss(input);
    std::cin.rdbuf(ss.rdbuf());
    char* text = Parser::readText();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(text, "");
    free(text);
}

TEST(ParserTest, ReadIntegerReturnsCorrectInteger) {
    testing::internal::CaptureStdout();
    std::string input = "42\n";
    std::istringstream ss(input);
    std::cin.rdbuf(ss.rdbuf());
    int num = Parser::readInteger("Enter a number: ");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(num, 42);
}

TEST(ParserTest, ReadIntegerHandlesInvalidInput) {
    testing::internal::CaptureStdout();
    std::string input = "invalid\n42\n";
    std::istringstream ss(input);
    std::cin.rdbuf(ss.rdbuf());
    int num = Parser::readInteger("Enter a number: ");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(num, 42);
}
