#pragma once

class Line {
public:
    char* text;
    Line* next;

    Line(char* userText);
    ~Line();
};

class LinkedList {
public:
    Line *head;
    Line *tail;
    int length;

    LinkedList();
    ~LinkedList();
};
