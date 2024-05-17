#include <cstdio>
#include "../include/parser.h"
#include "../include/text_storage.h"

int main(void) {
    int command;
    do {
        getValidCommand(&command);
        executeCommand(command);
    } while (command != 8);  // 8 - exit command

    return 0;
}
