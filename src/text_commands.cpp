#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/text_commands.h"

char* readText() {
    size_t bufferSize = 100; // Initial buffer size
    char *pBuffer = (char*)malloc(bufferSize * sizeof(char));
    char c;

    printf("Enter the text: ");
    while ((c = getchar()) != '\n') {
        if (strlen(pBuffer) == bufferSize - 1) { // Reallocate memory if needed
            bufferSize *= 2;
            pBuffer = (char*)realloc(pBuffer, bufferSize * sizeof(char));
        }
        pBuffer[strlen(pBuffer)] = c; // Append the character to the buffer
    }

    pBuffer[strlen(pBuffer)] = '\0'; // Add the null terminator

    return pBuffer;
}

void newLine(LinkedList* pContent) {
    char *pText = readText();
    // Handle an empty list
    if (pContent->head == nullptr) {
        pContent->head = createLine(pText);
        pContent->tail = pContent->head;
        return;
    }

    pContent->tail->next = createLine(pText);
    pContent->tail = pContent->tail->next;
    free(pText);
}

void printText(LinkedList* content) {
    Line* pCurrentLine = content->head;
    while (pCurrentLine != nullptr) {
        printf("%s\n", pCurrentLine->text);
        pCurrentLine = pCurrentLine->next;
    }
}
