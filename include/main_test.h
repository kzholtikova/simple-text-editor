#ifndef SIMPLE_TEXT_EDITOR_MAIN_TEST_H
#define SIMPLE_TEXT_EDITOR_MAIN_TEST_H

#include <gtest/gtest.h>
#include "../include/parser.h"

void setInput(const std::string& input);
std::string captureStdout(void (*func)(LinkedList*), LinkedList* list);
void redirectStdout();
void resetStdout();

class CommandsTest : public ::testing::Test {
protected:
    LinkedList *list;

    void SetUp() override {
        list = (LinkedList*)malloc(sizeof(LinkedList));
        list->head = nullptr;
        list->tail = nullptr;
        list->length = 0;
    }

    void TearDown() override {
        Line *current = list->head;
        while (current != nullptr) {
            Line *next = current->next;
            free(current->text);
            free(current);
            current = next;
        }

        free(list);
    }
};

#endif //SIMPLE_TEXT_EDITOR_MAIN_TEST_H
