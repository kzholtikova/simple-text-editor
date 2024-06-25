#pragma once
#include "text_storage.h"

class CaesarCipher {
public:
    CaesarCipher();
    ~CaesarCipher();

    void encryptText(LinkedList* content, int key);
    void decryptText(LinkedList* content, int key);
    void encryptFile(const char* filename, int key);
    void decryptFile(const char* filename, int key);
private:
    void* handle;
    char* (*encrypt)(const char*, int);
    char* (*decrypt)(const char*, int);
};
