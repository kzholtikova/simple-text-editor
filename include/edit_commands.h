#ifndef SIMPLE_TEXT_EDITOR_EDIT_COMMANDS_H
#define SIMPLE_TEXT_EDITOR_EDIT_COMMANDS_H

#include "text_storage.h"

char* readText();
void newLine(LinkedList* pContent);
void printText(LinkedList* content);
void appendText(LinkedList* content);
void insertBy(LinkedList* pContent);

#endif //SIMPLE_TEXT_EDITOR_EDIT_COMMANDS_H