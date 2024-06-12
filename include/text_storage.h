#pragma once

class Line {
public:
    char* text;
    Line* next;

    Line() {}; // Default constructor
    Line(const Line& other); // Copy constructor
    Line(const char* userText);
};

class LinkedList {
public:
    Line *head;
    Line *tail;
    int length;

    LinkedList();
    ~LinkedList();
};
