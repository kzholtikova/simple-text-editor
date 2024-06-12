#pragma once
#include "text_storage.h"
#include "commands_log.h"

class FileHandler {
public:
    static void saveToFile(LinkedList* content, const char* filename);
    static void loadFromFile(LinkedList* content, CommandsLog* cmdLog, const char* filename);
};
