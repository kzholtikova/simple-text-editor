#pragma once
#include "text_storage.h"
#include "parser.h"
#include "buffer.h"
#include "commands_log.h"
#include "editor.h"

class Application {
public:
    Application() : content(), cmdLog(content), editor(content, cmdLog), buffer(cmdLog)  {}; // Initializer list
    static void printCommandsInfo();
    static void clearConsole();
    void executeCommand();
    void run();
private:
    LinkedList content;
    int command;
    Editor editor;
    Buffer buffer;
    CommandsLog cmdLog;
};
