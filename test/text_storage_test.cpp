#include <gtest/gtest.h>
#include "../include/text_storage.h"
#include "../include/main_test.h"

class LineTest : public CommandsTest {
protected:
    char* text;
    Line* line;

    void SetUp() override {
        text = nullptr;
        line = nullptr;
    }

    void TearDown() override {
        if (line != nullptr) {
            free(line->text);
            free(line);
        }
    }
};

TEST_F(LineTest, CreateLineWithValidText) {
text = "Hello, world!";
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_STREQ(line->text, text);
EXPECT_EQ(line->next, nullptr);
}

TEST_F(LineTest, CreateLineWithEmptyText) {
text = "";
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_STREQ(line->text, text);
EXPECT_EQ(line->next, nullptr);
}

TEST_F(LineTest, CreateLineWithNullText) {
text = nullptr;
line = createLine(text);

ASSERT_NE(line, nullptr);
EXPECT_EQ(line->text, nullptr);
EXPECT_EQ(line->next, nullptr);
}
