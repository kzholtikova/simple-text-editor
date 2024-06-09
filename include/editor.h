#pragma once
#include "text_storage.h"

class Editor {
public:
    static void newLine(LinkedList* content, const char* text);
    static void printText(LinkedList* content);
    static void appendText(LinkedList* content, const char* text);
    static void insertBy(LinkedList* content, int lineIndex, int charIndex, const char* newText);
    static void search(LinkedList* content, const char* pattern);
    static void replaceBy(LinkedList* content, int lineIndex, int charIndex, const char* newText);
    static void deleteBy(LinkedList* content, int lineIndex, int charIndex, size_t length);
private:
    static Line* setPosition(LinkedList* content, int lineIndex, int charIndex);
};
