#pragma once
#include <iostream>
#include "text_storage.h"

class Buffer {
private:
    char* clip;
public:
    Buffer();

    char* getClip();
    void cut(LinkedList* content, int lineIndex, int charIndex, size_t length);
    void copy(LinkedList* content, int lineIndex, int charIndex, size_t length);
    void paste(LinkedList* content, int lineIndex, int charIndex);
};
