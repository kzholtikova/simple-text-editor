#pragma once
#include "text_storage.h"

class FileHandler {
public:
    static void saveToFile(LinkedList* content, const char* filename);
    static void loadFromFile(LinkedList* content, const char* filename);
};
