#include <iostream>
#include <vector>
#include "../include/text_storage.h"

Line::Line(const char* userText) {
    text = nullptr;
    if (userText)
        text = strdup(userText);  // Allocate memory for the 'str' copy, copies, returns a pointer
    next = nullptr;  // Initialize memory
}

Line::~Line() {
    if (text)
        free(text);  // Deallocate memory
}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

LinkedList::~LinkedList() {
    Line* current = head;
    while (current != nullptr) {
        Line* next = current->next;
        delete current;
        current = next;
    }
}

