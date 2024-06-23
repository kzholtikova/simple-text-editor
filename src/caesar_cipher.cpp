#include <iostream>
#include <dlfcn.h>
#include "../include/caesar_cipher.h"
#define LIBRARY_PATH "../lib/libcaesar_cipher.so"

CaesarCipher::CaesarCipher() {
    handle = dlopen(LIBRARY_PATH, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << "\n";
        return;
    }

    encrypt = (char* (*)(const char*, int))dlsym(handle, "encrypt");
    decrypt = (char* (*)(const char*, int))dlsym(handle, "decrypt");

    const char* dlsym_error = dlerror();
    if (!encrypt || !decrypt) {
        fprintf(stderr, "Error loading symbols: %s\n", dlerror());
        return;
    }
}

CaesarCipher::~CaesarCipher() {
    if (handle)
        dlclose(handle);
}

void CaesarCipher::encryptText(LinkedList* content, int key) {
    for (Line* line = content->head; line != nullptr; line = line->next) {
        if (line->text) {
            size_t length = strlen(line->text);
            char* encrypted = encrypt(line->text, key);
            delete[] line->text;
            line->text = new char[length + 1];
            std::copy(encrypted, encrypted + length + 1, line->text);
            delete[] encrypted;
        }
    }
}

void CaesarCipher::decryptText(LinkedList* content, int key) {
    for (Line* line = content->head; line != nullptr; line = line->next) {
        if (line->text) {
            size_t length = strlen(line->text);
            char* decrypted = decrypt(line->text, key);
            delete[] line->text;
            line->text = new char[length + 1];
            std::copy(decrypted, decrypted + length + 1, line->text);
            delete[] decrypted;
        }
    }
}
