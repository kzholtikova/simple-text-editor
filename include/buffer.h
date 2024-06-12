#pragma once
#include <iostream>
#include "text_storage.h"
#include "commands_log.h"

class Buffer {
private:
    char* clip;
public:
    Buffer();

    char* getClip();
    void cut(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex, size_t length);
    void copy(LinkedList* content, int lineIndex, int charIndex, size_t length);
    void paste(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex);
};
