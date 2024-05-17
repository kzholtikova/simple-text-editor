#include <gtest/gtest.h>
#include "../include/text_storage.h"

class LineTest : public ::testing::Test {
protected:
    char* text;
    Line* line;

    void TearDown() override {
        if (line != nullptr) {
            free(line->text);
            free(line);
        }
    }
};

TEST_F(LineTest, createLine_WithValidText_ReturnsLineWithText) {
text = "Hello, world!";
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_STREQ(line->text, text);
EXPECT_EQ(line->next, nullptr);
}

TEST_F(LineTest, createLine_WithEmptyText_ReturnsLineWithEmptyText) {
text = "";
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_STREQ(line->text, text);
EXPECT_EQ(line->next, nullptr);
}

TEST_F(LineTest, createLine_WithNullText_ReturnsLineWithNullText) {
text = nullptr;
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_EQ(line->text, nullptr);
EXPECT_EQ(line->next, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}