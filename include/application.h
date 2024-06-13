#pragma once
#include "text_storage.h"
#include "parser.h"
#include "buffer.h"
#include "commands_log.h"
#include "editor.h"
#include "cursor.h"

class Application {
public:
    Application() : content(), buffer(), cmdLog(), cursor() {}
    static void printCommandsInfo();
    static void clearConsole();
    void executeCommand();
    void run();

    LinkedList content;
    int command;
    Buffer buffer;
    CommandsLog cmdLog;
    Cursor cursor;
};
