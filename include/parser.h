#pragma once
#include "text_storage.h"

class Parser {
public:
    static char* readText();
    static int readInteger(const char* prompt);
};
