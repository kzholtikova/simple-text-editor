#include <iostream>
#include "../include/editor.h"

// const prevents modification passing read-only ref
void Editor::newLine(LinkedList* content, CommandsLog* cmdLog, const char* text) {
    Line *newLine = new Line(text);
    if (cmdLog)
        cmdLog->logBefore(nullptr, content->length);
    if (content->tail)
        content->tail->next = newLine;
    else // handle an empty list
        content->head = newLine;

    content->tail = newLine;
    content->length++;
    if (cmdLog)
        cmdLog->logAfter(text);
}

void Editor::printText(LinkedList* content) {
    for (Line *currentLine = content->head; currentLine; currentLine = currentLine->next)
        std::cout << currentLine->text << "\n";
}

void Editor::appendText(LinkedList* content, CommandsLog* cmdLog, const char* newText) {
    if (content->tail) {
        if (cmdLog)
            cmdLog->logBefore(content->tail->text, content->length - 1);
        size_t oldLength = strlen(content->tail->text), toAppendLength = strlen(newText);
        char* newLineText = new char[oldLength + toAppendLength + 1];
        std::copy(content->tail->text, content->tail->text + oldLength, newLineText);
        std::copy(newText, newText + toAppendLength + 1, newLineText + oldLength);
        delete[] content->tail->text;
        content->tail->text = newLineText;

        if (cmdLog)
            cmdLog->logAfter(content->tail->text);
    } else
        Editor::newLine(content, cmdLog, newText);
}

void Editor::search(LinkedList* content, const char* pattern) {
    size_t patternLen = strlen(pattern);
    bool found = false;
    int lineIndex = 0;
    for (Line *currentLine = content->head; currentLine; currentLine = currentLine->next, lineIndex++) {
        char *ocurrenceIndex = currentLine->text;
        while ((ocurrenceIndex = strstr(ocurrenceIndex, pattern))) {
            found = true;
            std::cout << "'" << pattern << "'" << " is at line " << lineIndex << ", index " << ocurrenceIndex - currentLine->text << ".\n";
            ocurrenceIndex += patternLen;
        }
    }

    if (!found) {
        std::cout << "'" << pattern << "'" << " is not found.\n";
    }
}

void Editor::insertText(CommandsLog* cmdLog, Cursor c, const char* newText) {
    Line* line = c.getCursorLine();
    int charIndex = c.getCursorCharIndex();
    if (cmdLog)
        cmdLog->logBefore(line->text, c.getCursorLineIndex());
    size_t oldLength = strlen(line->text), toInsertLength = strlen(newText);
    char* newLineText = new char[oldLength + toInsertLength + 1];
    std::copy(line->text, line->text + charIndex, newLineText);
    std::copy(newText, newText + toInsertLength + 1, newLineText + charIndex);
    // Move rest symbols
    std::copy(line->text + charIndex, line->text + oldLength + 1, newLineText + charIndex + toInsertLength);
    delete[] line->text;
    line->text = newLineText;

    if (cmdLog)
        cmdLog->logAfter(line->text);
}

void Editor::replaceText(CommandsLog* cmdLog, Cursor c, const char *newText) {
    Line* line = c.getCursorLine();
    int charIndex = c.getCursorCharIndex();
    if (cmdLog)
        cmdLog->logBefore(line->text, c.getCursorLineIndex());
    size_t oldLength = strlen(line->text), toReplaceLength = strlen(newText);
    if (toReplaceLength > oldLength - charIndex - 1) {
        char *newLineText = new char[oldLength - charIndex + toReplaceLength + 1];
        std::copy(line->text, line->text + charIndex, newLineText);
        delete[] line->text;
        line->text = newLineText;
    }
    std::copy(newText, newText + toReplaceLength, line->text + charIndex);

    if (cmdLog)
        cmdLog->logAfter(line->text);
}

void Editor::deleteText(CommandsLog* cmdLog, Cursor c, size_t length) {
    Line* line = c.getCursorLine();
    int charIndex = c.getCursorCharIndex();
    if (cmdLog)
        cmdLog->logBefore(line->text, c.getCursorLineIndex());
    if (length > strlen(line->text) - charIndex)
        length = strlen(line->text) - charIndex;
    std::copy(line->text + charIndex + length, line->text + strlen(line->text) + 1, line->text + charIndex);

    if (cmdLog)
        cmdLog->logAfter(line->text);
}
