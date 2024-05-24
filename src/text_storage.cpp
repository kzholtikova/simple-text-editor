#include <cstdlib>
#include <cstring>
#include "../include/text_storage.h"

Line* createLine(char* text) {
    Line *pLine = (Line*)malloc(sizeof(Line));  // Allocate memory to store 2 pointers
    if (pLine == nullptr)
        return nullptr;

    if (text != nullptr) {
        pLine->text = strdup(text);  // Allocate memory for the 'str' copy, copies, returns a pointer
        pLine->next = nullptr;  // Initialize memory
    } else
        pLine->text = nullptr;

    return pLine;
}
