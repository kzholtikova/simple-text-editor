#include <iostream>
#include "../include/commands_log.h"
#include "../include/editor.h"

CommandsLog::CommandsLog() {
    stackSize = 4;
    currentStackSize = 0;
    logStack = new LineLog[stackSize];
    topIndex = -1;
}

void CommandsLog::logBefore(const Line& line, int lineIndex) {
    if (stackSize == topIndex + 1) {
        stackSize *= 2;
        LineLog* newLogStack = new LineLog[stackSize];
        std::copy(logStack, logStack + topIndex + 1, newLogStack);
        delete[] logStack;
        logStack = newLogStack;
    }

    topIndex++;
    currentStackSize++;
    logStack[topIndex].before = Line(line);
    logStack[topIndex].lineIndex = lineIndex;
}

void CommandsLog::logAfter(const Line& line) {
    logStack[topIndex].after = Line(line);
}

void CommandsLog::undo(LinkedList* content) {
    if (topIndex != -1) {
        int lineIndex = -1;
        Line *currentLine = new Line();
        currentLine->next = content->head;
        while (lineIndex < logStack[topIndex].lineIndex - 1) {
            currentLine = currentLine->next;
            lineIndex++;
        }

        // handle newline command
        if (logStack[topIndex].before.text == nullptr && logStack[topIndex].after.text != nullptr) {
            delete[] currentLine->next;
            content->tail = currentLine;
            content->length--;
            if (lineIndex == 0)
                content->head = content->tail;
        } else {
            delete[] currentLine->next->text;
            currentLine->next->text = new char[strlen(logStack[topIndex].before.text) + 1];
            std::copy(logStack[topIndex].before.text,
                      logStack[topIndex].before.text + strlen(logStack[topIndex].before.text) + 1, currentLine->next->text);
            if (lineIndex == 0)
                content->head->text = currentLine->next->text;
        }

        topIndex--;
    } else
        std::cout << "Nothing to undo.\n";
}

void CommandsLog::redo(LinkedList* content) {
    if (topIndex + 1 < currentStackSize) {
        topIndex++;
        int lineIndex = -1;
        Line *currentLine = new Line();
        currentLine->next = content->head;
        while (lineIndex < logStack[topIndex].lineIndex - 1) {
            currentLine = currentLine->next;
            lineIndex++;
        }

        // redo newline command
        if (logStack[topIndex].before.text == nullptr && logStack[topIndex].after.text != nullptr)
            Editor::newLine(content, this, logStack[topIndex].after.text);
        else {
            delete[] currentLine->next->text;
            currentLine->next->text = new char[strlen(logStack[topIndex].after.text) + 1];
            std::copy(logStack[topIndex].after.text,
                      logStack[topIndex].after.text + strlen(logStack[topIndex].after.text) + 1, currentLine->next->text);
        }
    } else
        std::cout << "Nothing to redo.\n";
}

LineLog CommandsLog::getLineLog(int index) {
    if (index < currentStackSize)
        return logStack[index];
    return LineLog {};
}
