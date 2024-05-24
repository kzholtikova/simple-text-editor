#include <cstdio>
#include "../include/parser.h"
#include "../include/text_storage.h"

int main(void) {
    int command;
    LinkedList *pContent = new LinkedList();
    do {
        getValidInput(&command, 8, (char*)"Choose a command (0-8): ");
        executeCommand(command, pContent);
    } while (command != 8);  // 8 - exit command

    return 0;
}
