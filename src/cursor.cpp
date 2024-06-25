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
    lineIdx > 0 ? this->lineIndex = lineIdx : this->lineIndex = 0;
    this->charIndex = charIdx;
}

void Cursor::moveCursorRight(int steps) {
    charIndex += steps;
    if (line && charIndex > strlen(line->text))
        charIndex = strlen(line->text);
}

void Cursor::moveCursorLeft(int steps) {
    charIndex -= steps;
    if (line && charIndex < 0)
        charIndex = 0;
}
