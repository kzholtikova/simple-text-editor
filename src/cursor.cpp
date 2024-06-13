#include <iostream>
#include "../include/cursor.h"

Cursor::Cursor() {
    line = nullptr;
    lineIndex = 0;
    charIndex = 0;
}

Line* Cursor::getCursorLine() const {
    return line;
}

int Cursor::getCursorLineIndex() const {
    return lineIndex;
}

int Cursor::getCursorCharIndex() const {
    return charIndex;
}

void Cursor::setCursor(LinkedList *content, int lineIdx, int charIdx) {
    if (lineIdx < content->length) {
        Line* currentLine = content->head;
        for (int i = 0; i < lineIdx; i++)
            currentLine = currentLine->next;

        if (charIdx <= strlen(currentLine->text))
            updateCursor(currentLine, lineIdx, charIdx);
        else {
            std::cerr << "Char index is out of bounds.";
            std::cin.get();
        }
    } else {
        std::cerr << "Line index is out of bounds.";
        std::cin.get();
    }
}

void Cursor::updateCursor(Line *tail, int lineIdx, int charIdx) {
    this->line = tail;
    this->lineIndex = lineIdx;
    this->charIndex = charIdx;
}