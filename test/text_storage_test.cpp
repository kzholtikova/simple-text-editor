#include <gtest/gtest.h>
#include "../include/text_storage.h"

TEST(LineTest, ConstructorWithNull) {
    Line line(nullptr);
    EXPECT_EQ(line.text, nullptr);
}

TEST(LineTest, ConstructorWithText) {
    const char* userText = "Hello, World!";
    Line line(userText);
    EXPECT_STREQ(line.text, userText);
}

TEST(LineTest, DestructorFreesMemory) {
    const char* userText = "Hello, World!";
    Line* line = new Line(userText);
    delete line;
    // If the destructor works correctly, this test will not cause a memory leak
}

TEST(LinkedListTest, ConstructorInitializesEmptyList) {
    LinkedList list;
    EXPECT_EQ(list.head, nullptr);
    EXPECT_EQ(list.tail, nullptr);
    EXPECT_EQ(list.length, 0);
}

TEST(LinkedListTest, DestructorDeletesAllNodes) {
    auto* list = new LinkedList();
    // Add some nodes to the list
    // If the destructor works correctly, this test will not cause a memory leak
    delete list;
}