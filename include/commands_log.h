#pragma once
#include <cstddef>
#include "text_storage.h"

class CommandsLog {
private:
    LinkedList& content;
    Line* lineAfterStack;
    Line* lineBeforeStack;
    int* lineIndexStack;
    int topIndex;
    size_t stackSize;
public:
    CommandsLog(LinkedList& content);

    void logBefore(Line line, int lineIndex);
    void logAfter(Line line);
    void undo();
    void redo();
};