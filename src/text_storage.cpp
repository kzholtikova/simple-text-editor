#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/text_storage.h"

Line* createLine(char* text) {
    Line *line = (Line*)malloc(sizeof(Line));  // Allocate memory to store 2 pointers
    if (line == nullptr)
        return nullptr;

    if (text != nullptr) {
        line->text = strdup(text);  // Allocate memory for the 'str' copy, copies, returns a pointer
        line->next = nullptr;  // Initialize memory
    } else
        line->text = nullptr;

    return line;
}
