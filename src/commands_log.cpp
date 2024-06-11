#include <iostream>
#include "../include/commands_log.h"

CommandsLog::CommandsLog(LinkedList& content) : content(content) {
    stackSize = 4;
    lineAfterStack = new Line[stackSize];
    lineBeforeStack = new Line[stackSize];
    lineIndexStack = new int[stackSize];
    topIndex = -1;
}

void CommandsLog::logBefore(Line line, int lineIndex) {
    if (stackSize == topIndex + 1) {
        stackSize *= 2;
        Line* newLineStack = new Line[stackSize];
        Line* newPrevLineStack = new Line[stackSize];
        int *newLineIndexStack = new int[stackSize];
        std::copy(lineAfterStack, lineAfterStack + topIndex + 1, newLineStack);
        std::copy(lineBeforeStack, lineBeforeStack + topIndex + 1, newPrevLineStack);
        std::copy(lineIndexStack, lineIndexStack + topIndex + 1, newLineIndexStack);
        delete[] lineAfterStack;
        delete[] lineBeforeStack;
        delete[] lineIndexStack;
        lineAfterStack = newLineStack;
        lineBeforeStack = newPrevLineStack;
        lineIndexStack = newLineIndexStack;
    }

    topIndex++;
    lineBeforeStack[topIndex] = line;
    lineIndexStack[topIndex] = lineIndex;
}

void CommandsLog::logAfter(Line line) {
    lineAfterStack[topIndex] = line;
}

void CommandsLog::undo() {
    if (topIndex != -1) {
        int lineIndex = 0;
        Line *currentLine = content.head;
        while (lineIndex < lineIndexStack[topIndex] - 1) { // get the line preceding the one to undo
            currentLine = currentLine->next;
            lineIndex++;
        }

        if (lineIndex == 0) { // handle head
            content.head = &lineBeforeStack[topIndex];
        } else {
            currentLine->next = &lineBeforeStack[topIndex];
        }

        topIndex--;
    } else
        std::cout << "Nothing to undo.\n";
}

void CommandsLog::redo() {
    if (&lineAfterStack[topIndex + 1]) {
        topIndex++;
        int lineIndex = 0;
        Line *currentLine = content.head;
        while (lineIndex < lineIndexStack[topIndex] - 1) { // get the line preceding the one to undo
            currentLine = currentLine->next;
            lineIndex++;
        }

        if (lineIndex == 0) { // handle head
            content.head = &lineAfterStack[topIndex];
        } else {
            currentLine->next = &lineAfterStack[topIndex];
        }
    } else
        std::cout << "Nothing to redo.\n";
}

Line CommandsLog::getLineBefore(int index) {
    return lineBeforeStack[index];
}

Line CommandsLog::getLineAfter(int index) {
    return lineAfterStack[index];
}
