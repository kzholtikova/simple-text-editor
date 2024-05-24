#ifndef SIMPLE_TEXT_EDITOR_MAIN_TEST_H
#define SIMPLE_TEXT_EDITOR_MAIN_TEST_H

#include <gtest/gtest.h>
#include "../include/parser.h"

void setInput(const std::string& input);
void resetInput();
std::string captureStdout(void (*func)(LinkedList*), LinkedList* list);
void redirectStdout();
void resetStdout();

#endif //SIMPLE_TEXT_EDITOR_MAIN_TEST_H
