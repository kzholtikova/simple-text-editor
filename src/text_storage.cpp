#include <iostream>
#include "../include/text_storage.h"

Line::Line(const char* userText) {
    text = nullptr;
    if (userText) {
        text = new char[strlen(userText) + 1];  // Allocate memory for the 'str' copy
        std::copy(userText, userText + strlen(userText), text);  // Copy the string
    }
    next = nullptr;  // Initialize memory
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
