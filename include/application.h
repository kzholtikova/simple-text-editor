#pragma once
#include "text_storage.h"
#include "parser.h"
#include "buffer.h"

class Application {
public:
    Application() : content(), buffer() {}; // Initializer list
    static void printCommandsInfo();
    static void clearConsole();
    void executeCommand();
    void run();
private:
    LinkedList content;
    int command;
    Buffer buffer;
};
