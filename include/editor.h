#pragma once
#include "text_storage.h"
#include "commands_log.h"
#include "cursor.h"

class Editor {
public:
    static void newLine(LinkedList* content, CommandsLog* cmdLog, const char* text);
    static void printText(LinkedList* content);
    static void appendText(LinkedList* content, CommandsLog* cmdLog, const char* text);
    static void search(LinkedList* content, const char* pattern);
    static void insertText(CommandsLog* cmdLog, Cursor c, const char* newText);
    static void replaceText(CommandsLog* cmdLog, Cursor c, const char* newText);
    static void deleteText(CommandsLog* cmdLog, Cursor c, size_t length);
};
