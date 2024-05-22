#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/text_storage.h"

Line* createLine(char* text) {
    Line *pline = (Line*)malloc(sizeof(Line));  // Allocate memory to store 2 pointers
    if (pline == nullptr)
        return nullptr;

    if (text != nullptr) {
        pline->text = strdup(text);  // Allocate memory for the 'str' copy, copies, returns a pointer
        pline->next = nullptr;  // Initialize memory
    } else
        pline->text = nullptr;

    return pline;
}
