#pragma once
#include "text_storage.h"
#include "commands_log.h"

class Editor {
public:
    static void newLine(LinkedList* content, CommandsLog* cmdLog, const char* text);
    static void printText(LinkedList* content);
    static void appendText(LinkedList* content, CommandsLog* cmdLog, const char* text);
    static void search(LinkedList* content, const char* pattern);
    static void insertBy(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex, const char* newText);
    static void replaceBy(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex, const char* newText);
    static void deleteBy(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex, size_t length);
    static Line* setPosition(LinkedList* content, int lineIndex, int charIndex);
};
