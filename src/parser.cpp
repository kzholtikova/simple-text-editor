#include <cstdio>
#include "../include/parser.h"
# include "../include/text_commands.h"

// Functions definitions
void printCommandsInfo() {
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

// Validate if the input is an integer and is in the range specified
void getValidCommand(int* command) {
    char input;
    printf("Choose a command (1-8/ 0 - help): ");
    while (scanf("%d%c", command, &input) != 2 || input != '\n' || *command < 0 || *command > 8) {
        // clear the buffer to get correct new input
        if (input != '\n')
            while (getchar() != '\n');
        printf("Invalid input. Choose a command (1-8/ 0 - help): ");
    }
}

// Call the function related to the command number
void executeCommand(int command, LinkedList* pContent) {
    switch (command) {
        case 0:
            printCommandsInfo();
            return;
        case 1:
            appendText(pContent);
            return;
        case 2:
            newLine(pContent);
            return;
        case 3:
            printf("The command isn't implemented yet.\n");
            return;
        case 4:
            printf("The command isn't implemented yet.\n");
            return;
        case 5:
            printText(pContent);
            return;
        case 6:
            printf("The command isn't implemented yet.\n");
            return;
        case 7:
            printf("The command isn't implemented yet.\n");
            return;
        default:  // Exit the program
            printf("Bye!");
            return;
    }
}
