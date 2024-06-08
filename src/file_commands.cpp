#include <iostream>
#include "../include/file_commands.h"
#include "../include/edit_commands.h"

void FileHandler::saveToFile(LinkedList* content, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file) {
        for (Line *currentLine = content->head; currentLine; currentLine = currentLine->next) {
            fputs(currentLine->text, file);
            fputc('\n', file); // line end
        }

        fclose(file);
        std::cout << "Text has been successfully saved.\n";
    } else
        std::cerr << "Error opening file: " << filename << std::endl;
}

void FileHandler::loadFromFile(LinkedList* content, const char* filename) {
    FILE* file = fopen(filename, "r"); // default mode: text
    if (file) {
        char *lineText = nullptr;
        size_t lineSize = 0;
        ssize_t length;
        while ((length = getline(&lineText, &lineSize, file)) != -1) {
            if (length > 0 && lineText[length - 1] == '\n')
                lineText[length - 1] = '\0'; // Remove the newline character
            Editor::newLine(content, lineText);
        }

        fclose(file);
        delete[] lineText;
        std::cout << "Text has been successfully loaded.\n";
    } else
        std::cerr << "Error opening file: " << filename << std::endl;
}
