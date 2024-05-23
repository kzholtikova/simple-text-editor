#include <cstdio>
#include "../include/parser.h"
# include "../include/edit_commands.h"

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
void getValidInput(int* result, int upperBound, const char* prompt) {
    char input;
    int status;
    printf("%s", prompt);
    while ((status = scanf("%d%c", result, &input)) != 2 || input != '\n' || *result < 0 || *result > upperBound) {
        // clear the buffer to get correct new input
        int res = *result;
        if (input != '\n' || status != 2)
            while (getchar() != '\n');

        printf("%s", prompt);
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
            insertBy(pContent);
            return;
        default:  // Exit the program
            printf("Bye!");
            return;
    }
}
