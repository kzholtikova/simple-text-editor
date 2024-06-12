#pragma once
#include <cstddef>
#include "text_storage.h"

typedef struct LineLog {
    Line before = nullptr;
    Line after = nullptr;
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

    void logBefore(const Line& line, int lineIndex);
    void logAfter(const Line& line);
    void undo(LinkedList* content);
    void redo(LinkedList* content);
};