#ifndef SIMPLE_TEXT_EDITOR_FILE_COMMANDS_H
#define SIMPLE_TEXT_EDITOR_FILE_COMMANDS_H

#include <cstdio>
#include "text_storage.h"

FILE* openFile(const char* mode);
void saveToFile(LinkedList* pContent);
void loadFromFile(LinkedList* pContent);

#endif //SIMPLE_TEXT_EDITOR_FILE_COMMANDS_H
