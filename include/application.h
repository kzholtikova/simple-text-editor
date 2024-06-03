#pragma once
#include "text_storage.h"
#include "parser.h"

class Application {
public:
    LinkedList* content = new LinkedList();;
    int command;

    static void printCommandsInfo();
    static void clearConsole();
    void executeCommand();
    void run();
};
