#pragma once
#include "editor.h"

class FileHandler {
public:
    static void saveToFile(Editor editor, const char* filename);
    static void loadFromFile(Editor editor,  const char* filename);
};
