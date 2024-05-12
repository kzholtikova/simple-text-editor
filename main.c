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

int GetValidCommand(void) {
    printCommandsInfo();

    int command = readCommand();
    while (command < 0 || command > 8) {
        printf("The command %d doesn't exist.\n", command);
        command = readCommand();
    }

    return command;
}

int main(void) {
    int command = GetValidCommand();
    printf("%d", command);

    return 0;
}