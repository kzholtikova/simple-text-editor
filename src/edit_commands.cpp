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

    if (!found) {
        std::cerr << "'" << pattern << "'" << " is not found.\n";
        std::cin.get();
    }
}

void Editor::insertBy(LinkedList* content, int lineIndex, int charIndex, const char* newText) {
    Line *line = setPosition(content, lineIndex, charIndex);
    if (line) {
        size_t oldLength = strlen(line->text);
        size_t toInsertLength = strlen(newText);
        line->text = (char*)realloc(line->text, (oldLength + toInsertLength + 1) * sizeof(char));
        // Move rest symbols and insert at the specified index
        std::copy(line->text + charIndex, line->text + oldLength + 1, line->text + charIndex + toInsertLength);
        std::copy(newText, newText + toInsertLength, line->text + charIndex);
    }
}

void Editor::replaceBy(LinkedList *content, int lineIndex, int charIndex, const char *newText) {
    Line *line = setPosition(content, lineIndex, charIndex);
    if (line)
        std::copy(newText, newText + strlen(newText), line->text + charIndex);
}

void Editor::deleteBy(LinkedList *content, int lineIndex, int charIndex, size_t length) {
    Line *line = setPosition(content, lineIndex, charIndex);
    if (line)
        std::copy(line->text + charIndex + length, line->text + strlen(line->text) + 1, line->text + charIndex);
}

Line* Editor::setPosition(LinkedList *content, int lineIndex, int charIndex) {
    Line *line = content->head;
    for (int i = 0; line && i < lineIndex; i++)
        line = line->next;

    if (line) {
        if (charIndex >= 0 || charIndex <= strlen(line->text))
            return line;
        std::cerr << "Symbol index out of bounds.\n";
        std::cin.get();
    } else {
        std::cerr << "Line index out of bounds.\n";
        std::cin.get();
    }

    return nullptr;
}