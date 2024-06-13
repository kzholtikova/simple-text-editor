#pragma once
#include <iostream>
#include "text_storage.h"
#include "commands_log.h"
#include "cursor.h"

class Buffer {
private:
    char* clip;
public:
    Buffer();

    char* getClip();
    void cut(CommandsLog* cmdLog, Cursor c, size_t length);
    void copy(Cursor c, size_t length);
    void paste(CommandsLog* cmdLog, Cursor c);
};
