#include <iostream>
#include "../include/parser.h"

char* Parser::readText() {
    int bufferSize = 256; // Initial buffer size
    char *buffer = (char*)malloc(bufferSize * sizeof(char)), *text = (char*)malloc(1);
    text[0] = '\0';
    size_t textSize = 0; // string length

    std::cout << "Enter the text: ";
    while (fgets(buffer, bufferSize, stdin)) {
        textSize += strlen(buffer);
        text = (char*)realloc(text, textSize + 1); // Reallocate memory if needed
        strcat(text, buffer);
        if (buffer[strlen(buffer) - 1] == '\n')
            break;
    }

    text[textSize - 1] = '\0';
    free(buffer); // Free the memory that's no longer needed
    return text;
}

 int Parser::readInteger(const char* prompt) {
    int num;
    std::cout << prompt;
    while (!(std::cin >> num) || num < 0) {
        std::cout << "\nInvalid input. " << prompt;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline
    }
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any extra characters
     return num;
}

