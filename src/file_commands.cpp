#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/text_storage.h"

FILE* openFile(const char* mode) {
    char fileName[100];
    printf("Enter the file name: ");
    scanf("%s", fileName);
    return fopen(fileName, mode);
}

void saveToFile(LinkedList* pContent) {
    FILE* file = openFile("a");
    if (file == nullptr) {
        printf("Error opening file.\n");
        return;
    }

    Line *pCurrentLine = pContent->head;
    while (pCurrentLine != nullptr) {
        fputs(pCurrentLine->text, file);
        fputc('\n', file);
        pCurrentLine = pCurrentLine->next;
    }

    printf("Text has been saved successfully.\n");
    free(pCurrentLine);
    fclose(file);
}

void loadFromFile(LinkedList* pContent) {
    FILE* file = openFile("r");
    if (file == nullptr) {
        printf("Error opening file.\n");
        return;
    }

    char *pLine = nullptr;
    size_t lineSize = 0;
    ssize_t length;
    while ((length = getline(&pLine, &lineSize, file)) != -1) {
        if (pLine[length - 1] == '\n')
            pLine[length - 1] = '\0'; // Remove the newline character

        if (pContent->head == nullptr) { // Handle an empty list
            pContent->head = createLine(pLine);
            pContent->tail = pContent->head;
        } else {
            pContent->tail->next = createLine(pLine);
            pContent->tail = pContent->tail->next;
        }
        pContent->length++;
    }

    printf("Text has been loaded successfully.\n");
    free(pLine);
    fclose(file);
}
