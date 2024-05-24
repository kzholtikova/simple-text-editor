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
