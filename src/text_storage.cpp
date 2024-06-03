#include <iostream>
#include "../include/text_storage.h"

Line::Line(char* userText) {
    if (userText != nullptr) {
        text = strdup(text);  // Allocate memory for the 'str' copy, copies, returns a pointer
        next = nullptr;  // Initialize memory
    } else
        text = nullptr;
}

Line::~Line() {
    if (text != nullptr)
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

