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

void getValidCommand(int* command) {
    printf("Choose a command (1-8/ 0 - help): ");
    while (scanf("%d", command) == 0 || *command < 0 || *command > 8) {
        printf("Invalid input. Choose a command (1-8/ 0 - help): ");
        while (getchar() != '\n');
    }
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
        default:
            printf("Bye!");
            return;
    }
}

int main(void) {
    int command;
    do {
        getValidCommand(&command);
        executeCommand(command);
    } while (command != 8);

    return 0;
}