#include <stdio.h>

void printCommandsInfo(void) {
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

int readCommand(void){
    int userInput;
    printf("Choose a command (1-8/ 0 - help): ");
    scanf("%d", &userInput);

    return userInput;
}

void executeCommand(int command){
    switch (command) {
        case 0:
            printCommandsInfo();
            return;
        case 1:
            printf("The command isn't implemented yet.\n");
            return;
        case 2:
            printf("The command isn't implemented yet.\n");
            return;
        case 3:
            printf("The command isn't implemented yet.\n");
            return;
        case 4:
            printf("The command isn't implemented yet.\n");
            return;
        case 5:
            printf("The command isn't implemented yet.\n");
            return;
        case 6:
            printf("The command isn't implemented yet.\n");
            return;
        case 7:
            printf("The command isn't implemented yet.\n");
            return;
        case 8:
            printf("Bye!");
            return;
        default:
            printf("The command %d doesn't exist.\n", command);
            return;
    }
}

int main(void) {
    int command;
    do {
        command = readCommand();
        executeCommand(command);
    } while (command != 8);

    return 0;
}