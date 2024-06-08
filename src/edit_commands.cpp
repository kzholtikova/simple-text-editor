#include <iostream>
#include "../include/edit_commands.h"

// const prevents modification passing read-only ref
void Editor::newLine(LinkedList* content, const char* text) {
    Line* newLine = new Line(text);
    if (content->tail)
        content->tail->next = newLine;
    else // handle an empty list
        content->head = newLine;

    content->tail = newLine;
    content->length++;
}

void Editor::printText(LinkedList* content) {
    for (Line *currentLine = content->head; currentLine; currentLine = currentLine->next)
        std::cout << currentLine->text << "\n";
}

void Editor::appendText(LinkedList* content, const char* newText) {
    if (content->tail) {
        content->tail->text = (char *)realloc(content->tail->text,
                                              (strlen(content->tail->text) + strlen(newText) + 1) * sizeof(char));
        strcat(content->tail->text, newText);
    } else
        Editor::newLine(content, newText);
}

//        Parser::getValidInteger(&lineIndex, content->length - 1, (char*)"Enter a line index: ");
//        Parser::getValidInteger(&symbolIndex, strlen(line->text), (char*)"Enter a symbol index: ");
void Editor::insertBy(LinkedList* content, int lineIndex, int charIndex, const char* newText) {
    Line *line = content->head;
    for (int i = 0; line && i < lineIndex; i++)
        line = line->next;

    if (line) {
        size_t oldLength = strlen(line->text);
        size_t toInsertLength = strlen(newText);
        if (charIndex >= 0 && charIndex <= strlen(line->text)) {
            line->text = (char*)realloc(line->text, (oldLength + toInsertLength + 1) * sizeof(char));
            // Move rest symbols and insert at the specified index
            memmove(line->text + charIndex + toInsertLength, line->text + charIndex, oldLength - charIndex + 1);
            memcpy(line->text + charIndex, newText, toInsertLength);
        } else
            std::cerr << "Symbol index out of bounds." << std::endl;
    } else
        std::cerr << "Line index out of bounds." << std::endl;
}

void Editor::search(LinkedList* content, const char* pattern) {
    size_t patternLen = strlen(pattern);
    bool found = false;
    int lineIndex = 0;
    for (Line *currentLine = content->head; currentLine; currentLine = currentLine->next, lineIndex++) {
        char *ocurrenceIndex = currentLine->text;
        while ((ocurrenceIndex = strstr(ocurrenceIndex, pattern))) {
            found = true;
            std::cout << "'" << pattern << "'" << "found at line " << lineIndex << ", index " << ocurrenceIndex - currentLine->text << "\n";
            ocurrenceIndex += patternLen;
        }
    }

    if (!found)
        std::cerr << "'" << pattern << "'" << " is not found" << std::endl;
}
