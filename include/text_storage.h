#ifndef SIMPLE_TEXT_EDITOR_TEXT_STORAGE_H
#define SIMPLE_TEXT_EDITOR_TEXT_STORAGE_H

// LinkedList node structure
typedef struct Line {
    char *text;  // Array of chars to store a string
    Line *next;
} Line;

// Doubly linked list
typedef struct LinkedList {
    Line *head;
    Line *tail;
} LinkedList;

Line* createLine(char* text);

#endif //SIMPLE_TEXT_EDITOR_TEXT_STORAGE_H
