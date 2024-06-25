#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include "../include/caesar_cipher.h"
#define LIBRARY_PATH "../lib/libcaesar_cipher.so"
#define CHUNK_SIZE 128

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

void CaesarCipher::processText(LinkedList* content, int key, char* (*function)(const char*, int)) {
    for (Line* line = content->head; line != nullptr; line = line->next) {
        if (line->text) {
            size_t length = strlen(line->text);
            char* processed = function(line->text, key);
            delete[] line->text;
            line->text = new char[length + 1];
            std::copy(processed, processed + length + 1, line->text);
            delete[] processed;
        }
    }
}

void CaesarCipher::encryptText(LinkedList* content, int key) {
    processText(content, key, encrypt);
}

void CaesarCipher::decryptText(LinkedList* content, int key) {
    processText(content, key, decrypt);
}

void CaesarCipher::processFile(const char* filename, int key, char* (*function)(const char*, int)) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
    if (file.is_open()) {
        char buffer[CHUNK_SIZE];
        size_t fileSize = file.tellg();
        file.seekg(0);
        while (fileSize > 0) {
            size_t readChunkSize = fileSize > CHUNK_SIZE ? CHUNK_SIZE : fileSize;
            file.read(buffer, readChunkSize);
            char* processed = function(buffer, key);
            file.seekp(static_cast<std::streamoff>(file.tellg()) - file.gcount());
            file.write(processed, file.gcount());
            fileSize -= file.gcount();
            delete[] processed;
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << "\n";
        std::cin.get();
    }
}

void CaesarCipher::encryptFile(const char *filename, int key) {
    processFile(filename, key, encrypt);
}

void CaesarCipher::decryptFile(const char *filename, int key) {
    processFile(filename, key, decrypt);
}
