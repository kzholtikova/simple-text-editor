#pragma once
#include <cstddef>
#include "text_storage.h"

class CommandsLog {
private:
    Line** lineStack;
    int* lineIndexStack;
    int topIndex;
    size_t stackSize;
public:
    CommandsLog();

    void log(Line* line, int lineIndex);
    void undo();
    void redo();
};