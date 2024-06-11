#pragma once
#include "text_storage.h"
#include "commands_log.h"

class Editor {
private:
    CommandsLog& cmdLog;
public:
    LinkedList& content;
    Editor(LinkedList& content, CommandsLog& cmdLog) : content(content), cmdLog(cmdLog) {};

    void newLine(const char* text);
    void printText() const;
    void appendText(const char* text);
    void search(const char* pattern);
    void insertBy(int lineIndex, int charIndex, const char* newText);
    void replaceBy(int lineIndex, int charIndex, const char* newText);
    void deleteBy(int lineIndex, int charIndex, size_t length);
    Line* setPosition(int lineIndex, int charIndex);
};
