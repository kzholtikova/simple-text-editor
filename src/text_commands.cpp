#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/text_commands.h"

char* readText() {
    size_t bufferSize = 100; // Initial buffer size
    char *pBuffer = (char*)malloc(bufferSize * sizeof(char));
    char c;
    size_t currentSize = 0; // Read string size

    printf("Enter the text: ");
    while ((c = getchar()) != '\n') {
        if (currentSize == bufferSize - 1) { // Reallocate memory if needed
            bufferSize *= 2;
            pBuffer = (char*)realloc(pBuffer, bufferSize * sizeof(char));
        }
        pBuffer[currentSize++] = c; // Append the character to the buffer
    }

    pBuffer[currentSize] = '\0'; // Add the null terminator

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
    free(pText); // Free memory that's no longer needed
}

void printText(LinkedList* content) {
    Line* pCurrentLine = content->head;
    while (pCurrentLine != nullptr) {
        printf("%s\n", pCurrentLine->text);
        pCurrentLine = pCurrentLine->next;
    }
}

void appendText(LinkedList* content) {
    char *newText = readText();
    // Allocate memory for the new text + old text
    content->tail->text = (char*)realloc(content->tail->text, (strlen(content->tail->text) + strlen(newText) + 1) * sizeof(char));
    strcat(content->tail->text, newText);
    free(newText); // Free memory that's no longer needed
}
