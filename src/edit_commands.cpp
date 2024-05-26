#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/edit_commands.h"
#include "../include/parser.h"

char* readText() {
    size_t bufferSize = 100; // Initial buffer size
    char *pBuffer = (char*)malloc(bufferSize * sizeof(char));
    char c;
    size_t currentSize = 0; // Read string size

    printf("Enter the text: ");
    while ((c = getchar()) != '\n' && c != EOF) {
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
        pContent->length = 1;
        return;
    }

    pContent->tail->next = createLine(pText);
    pContent->tail = pContent->tail->next;
    pContent->length++;
    free(pText); // Free memory that's no longer needed
}

void printText(LinkedList* pContent) {
    Line *pCurrentLine = pContent->head;
    while (pCurrentLine != nullptr) {
        printf("%s\n", pCurrentLine->text);
        pCurrentLine = pCurrentLine->next;
    }
    free(pCurrentLine);
}

void appendText(LinkedList* pContent) {
    if (pContent->head == nullptr)
        newLine(pContent);
    else {
        char *newText = readText();
        // Allocate memory for the new text + old text
        pContent->tail->text = (char*)realloc(pContent->tail->text, (strlen(pContent->tail->text) + strlen(newText) + 1) * sizeof(char));
        strcat(pContent->tail->text, newText);
        free(newText); // Free memory that's no longer needed
    }
}

void insertBy(LinkedList* pContent) {
    if (pContent->length != 0) {
        int lineIndex;     // Read valid line index and obtain it
        getValidInput(&lineIndex, pContent->length - 1, (char*)"Enter a line index: ");
        Line *pLine = pContent->head;
        for (int i = 0; i < lineIndex; ++i) {
            pLine = pLine->next;
        }

        int symbolIndex; // Read valid symbol index
        getValidInput(&symbolIndex, strlen(pLine->text), (char*)"Enter a symbol index: ");
        char *pText = readText();
        // Reallocate memory for the new text
        int oldLength = strlen(pLine->text);
        int toInsertLength = strlen(pText);
        pLine->text = (char*)realloc(pLine->text, (oldLength + toInsertLength + 1) * sizeof(char));
        // Move rest symbols and insert at the specified index
        memmove(pLine->text + symbolIndex + toInsertLength, pLine->text + symbolIndex, oldLength - symbolIndex + 1);
        memcpy(pLine->text + symbolIndex, pText, toInsertLength);

        free(pText);
    } else {
        printf("No lines to insert to.\n");
    }
}
