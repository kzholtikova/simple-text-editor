#include <iostream>
#include "../include/commands_log.h"

CommandsLog::CommandsLog() {
    stackSize = 4;
    lineStack = new Line*[stackSize];
    lineIndexStack = new int[stackSize];
    topIndex = -1;
}

void CommandsLog::log(Line* line, int lineIndex) {
    if (stackSize == topIndex + 1) {
        stackSize *= 2;
        Line** newLineStack = new Line*[stackSize];
        int *newLineIndexStack = new int[stackSize];
        std::copy(lineStack, lineStack + topIndex + 1, newLineStack);
        std::copy(lineIndexStack, lineIndexStack + topIndex + 1, newLineIndexStack);
        delete[] lineStack;
        delete[] lineIndexStack;
        lineStack = newLineStack;
        lineIndexStack = newLineIndexStack;
    }

    topIndex++;
    lineStack[topIndex] = line;
    lineIndexStack[topIndex] = lineIndex;
}
