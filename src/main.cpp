#include <cstdio>
#include "../include/parser.h"
#include "../include/text_storage.h"

int main(void) {
    int command;
    LinkedList *pContent = new LinkedList();
    do {
        getValidCommand(&command);
        executeCommand(command, pContent);
    } while (command != 8);  // 8 - exit command

    return 0;
}
