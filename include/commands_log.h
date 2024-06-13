#pragma once
#include <cstddef>
#include "text_storage.h"
#include "cursor.h"

typedef struct LineLog {
    char* before = nullptr;
    char* after = nullptr;
    int lineIndex;
} LineLog;

class CommandsLog {
private:
    LineLog* logStack;
    int topIndex;
    size_t currentStackSize;
    size_t stackSize;
public:
    CommandsLog();
    LineLog getLineLog(int index);

    void logBefore(const char* text, int lineIndex);
    void logAfter(const char* text);
    void undo(LinkedList* content, Cursor& cursor);
    void redo(LinkedList* content, Cursor& cursor);
};