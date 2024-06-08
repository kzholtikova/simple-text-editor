#include <iostream>
#include "../include/parser.h"

char* Parser::readText() {
    int bufferSize = 256; // Initial buffer size
    char *buffer = (char*)malloc(bufferSize * sizeof(char)), *text = (char*)malloc(1);
    text[0] = '\0';
    size_t textSize = 0; // string length

    std::cout << "Enter the text: ";
    while (std::cin.getline(buffer, bufferSize)) {
        textSize += std::cin.gcount();
        char* new_text = new char[textSize + 1]; // Allocate memory for new text
        strcpy(new_text, text); // Copy old text to new text
        strcat(new_text, buffer); // Append buffer to new text
        delete[] text; // Delete old text
        text = new_text; // Update text pointer
        if (std::cin.eof()) {
            break;
        }
    }

    delete[] buffer; // Free the memory that's no longer needed
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

