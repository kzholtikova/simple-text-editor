#pragma once
#include "text_storage.h"

class Cursor {
private:
    Line* line;
    int lineIndex;
    int charIndex;
public:
    Cursor();
    Line* getCursorLine() const; // const prevents the method from modifying the object
    int getCursorLineIndex() const;
    int getCursorCharIndex() const;
    void setCursor(LinkedList *content, int lineIdx, int charIdx);
    void updateCursor(Line *tail, int lineIdx, int charIdx);
    void moveCursorRight(int steps);
    void moveCursorLeft(int steps);
};
