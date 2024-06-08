#pragma once
#include "text_storage.h"
#include "parser.h"

class Application {
public:
    static void printCommandsInfo();
    static void clearConsole();
    void executeCommand();
    void run();
private:
    LinkedList* content = new LinkedList();;
    int command;
};
