#ifndef SIMPLE_TEXT_EDITOR_PARSER_H
#define SIMPLE_TEXT_EDITOR_PARSER_H

#include "text_storage.h"

// functions declarations
void printCommandsInfo();
void getValidInput(int* result, int upperBound, const char* prompt);
void executeCommand(int command, LinkedList* pContent);

#endif // SIMPLE_TEXT_EDITOR_PARSER_H
