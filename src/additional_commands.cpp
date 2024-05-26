#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../include/additional_commands.h"
#include "../include/edit_commands.h"

void clearConsole() {
    printf("\e[1;1H\e[2J"); // RegEx using ANSI escape codes
}

void search(LinkedList* pContent) {
    char *pPattern = readText();
    size_t patternLength = strlen(pPattern);

    bool found = false;
    int lineIndex = 0;
    Line *pCurrentLine = pContent->head;
    char  *pSymbolIndex, *pCurrentSymbol;
    while(pCurrentLine != nullptr) {
        pCurrentSymbol = pCurrentLine->text;
        while((pSymbolIndex = strstr(pCurrentSymbol, pPattern)) != nullptr) {
            found = true;
            printf("'%s' found at line %d, index %ld\n", pPattern, lineIndex, pSymbolIndex - pCurrentLine->text);
            pCurrentSymbol = pSymbolIndex + patternLength;
        }

        pCurrentLine = pCurrentLine->next;
        lineIndex++;
    }

    if (!found)
        printf("'%s' is not found\n", pPattern);
    free(pPattern);
}
