#include <iostream>
#include "../include/commands_log.h"
#include "../include/editor.h"

CommandsLog::CommandsLog() {
    stackSize = 4;
    currentStackSize = 0;
    logStack = new LineLog[stackSize];
    topIndex = -1;
}

void CommandsLog::logBefore(const char* text, int lineIndex) {
    if (stackSize == topIndex + 1) {
        stackSize *= 2;
        auto* newLogStack = new LineLog[stackSize];
        std::copy(logStack, logStack + topIndex + 1, newLogStack);
        delete[] logStack;
        logStack = newLogStack;
    }

    topIndex++;
    if (logStack[topIndex].before == nullptr && logStack[topIndex].after == nullptr)
        currentStackSize++;
    if (text) {
        delete[] logStack[topIndex].before;
        logStack[topIndex].before = new char[strlen(text) + 1];
        std::copy(text, text + strlen(text) + 1, logStack[topIndex].before);
    }
    logStack[topIndex].lineIndex = lineIndex;
}

void CommandsLog::logAfter(const char* text) {
    if (text) {
        delete[] logStack[topIndex].after;
        logStack[topIndex].after = new char[strlen(text) + 1];
        std::copy(text, text + strlen(text) + 1, logStack[topIndex].after);
    }
}

void CommandsLog::undo(LinkedList* content, Cursor &c) {
    if (topIndex != -1) {
        int lineIndex = -1;
        Line *currentLine = new Line();
        currentLine->next = content->head;
        while (lineIndex < logStack[topIndex].lineIndex - 1) {
            currentLine = currentLine->next;
            lineIndex++;
        }

        // handle newline command
        if (logStack[topIndex].before == nullptr && logStack[topIndex].after != nullptr) {
            if (logStack[topIndex].lineIndex == 0) {
                content->tail = nullptr;
                content->head = content->tail;
            } else {
                delete currentLine->next;
                currentLine->next = nullptr;
                content->tail = currentLine;
            }
            content->length--;
            c.updateCursor(content->tail, content->length - 1, 0);
        } else {
            delete[] currentLine->next->text;
            currentLine->next->text = new char[strlen(logStack[topIndex].before) + 1];
            std::copy(logStack[topIndex].before,
                      logStack[topIndex].before + strlen(logStack[topIndex].before) + 1, currentLine->next->text);
            if (logStack[topIndex].lineIndex == 0)
                content->head->text = currentLine->next->text;
        }

        topIndex--;
    } else
        std::cout << "Nothing to undo.\n";
}

void CommandsLog::redo(LinkedList* content, Cursor &c) {
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
        if (logStack[topIndex].before == nullptr && logStack[topIndex].after != nullptr) {
            Editor::newLine(content, nullptr, logStack[topIndex].after);
            c.updateCursor(content->tail, content->length - 1, 0);
        } else {
            delete[] currentLine->next->text;
            currentLine->next->text = new char[strlen(logStack[topIndex].after) + 1];
            std::copy(logStack[topIndex].after,
                      logStack[topIndex].after + strlen(logStack[topIndex].after) + 1, currentLine->next->text);
        }
    } else
        std::cout << "Nothing to redo.\n";
}

LineLog CommandsLog::getLineLog(int index) {
    if (index < currentStackSize)
        return logStack[index];
    return LineLog();
}
