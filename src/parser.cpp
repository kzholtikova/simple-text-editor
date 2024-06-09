#include <iostream>
#include "../include/parser.h"

char* Parser::readText() {
    int bufferSize = 256; // Initial buffer size
    char *buffer = new char[bufferSize + 1];

    std::cout << "Enter the text: ";
    std::cin.getline(buffer, bufferSize);
    while (!std::cin.eof() && std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bufferSize *= 2; // Double the buffer size
        char* new_buffer = new char[bufferSize + 1]; // Allocate memory for new buffer
        delete[] buffer; // Free the old buffer
        buffer = new_buffer; // Update buffer pointer
        std::cin.getline(buffer, bufferSize);
    }
    char* text = new char[bufferSize + 1]; // Allocate memory for new text
    text[0] = '\0'; // Initialize text
    strncat(text, buffer, bufferSize); // Append buffer to new text

    delete[] buffer; // Free the memory that's no longer needed
    return text;
}

 int Parser::readInteger(const char* prompt) {
    int num;
    std::cout << prompt;
    while (!(std::cin >> num) || num < 0) {
        std::cout << "Invalid input. " << prompt;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline
    }
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any extra characters
     return num;
}

