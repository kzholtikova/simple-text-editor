#pragma once
#include <iostream>
#include "commands_log.h"
#include "editor.h"

class Buffer {
private:
    char* clip;
    CommandsLog& cmdLog;
public:
    Buffer(CommandsLog& cmdLog);

    char* getClip();
    void cut(Editor editor, int lineIndex, int charIndex, size_t length);
    void copy(Editor editor, int lineIndex, int charIndex, size_t length);
    void paste(Editor editor, int lineIndex, int charIndex);
};
