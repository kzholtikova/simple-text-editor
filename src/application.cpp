#include <iostream>
#include "../include/application.h"
#include "../include/additional_commands.h"
#include "../include/edit_commands.h"
#include "../include/file_commands.h"

void Application::printCommandsInfo() {
    printf("0 - Help\n"
           "1 - Append to the end\n"
           "2 - New line\n"
           "3 - Save into the file\n"
           "4 - Load from the file\n"
           "5 - Print current text\n"
           "6 - Insert by line and index\n"
           "7 - Search\n"
           "8 - Exit\n");
}

void  Application::clearConsole() {
    printf("\e[1;1H\e[2J"); // RegEx using ANSI escape codes
}

// Call the function related to the command number
void  Application::executeCommand() {
    switch (command) {
        case 0:
            printCommandsInfo();
            return;
        case 1:
            appendText(content);
            return;
        case 2:
            newLine(content);
            return;
        case 3:
            saveToFile(content);
            return;
        case 4:
            loadFromFile(content);
            return;
        case 5:
            printText(content);
            return;
        case 6:
            insertBy(content);
            return;
        case 7:
            search(content);
            return;
        default:  // Exit the program
            printf("Bye!");
            return;
    }
}

void Application::run() {
    do {
        Parser::getValidInput(&command, 8, (char*)"Choose a command (0-8): ");
        clearConsole();
        executeCommand();
    } while (command != 8);  // 8 - exit command
}
