#include "../include/buffer.h"
#include "../include/editor.h"

Buffer::Buffer() {
    clip = nullptr; // buffer text
}

void Buffer::cut(LinkedList *content, int lineIndex, int charIndex, size_t length) {
    copy(content, lineIndex, charIndex, length);
    Editor::deleteBy(content, lineIndex, charIndex, length);
}

void Buffer::copy(LinkedList *content, int lineIndex, int charIndex, size_t length) {
    Line *line = Editor::setPosition(content, lineIndex, charIndex);
    if (line) {
        if (clip)
            delete[] clip; // deallocate to avoid a memory leak
        clip = new char[length + 1];
        std::copy(line->text + charIndex, line->text + charIndex + length, clip);
        clip[length] = '\0'; // null-terminate the string
    }
}

void Buffer::paste(LinkedList *content, int lineIndex, int charIndex) {
    Editor::insertBy(content, lineIndex, charIndex, clip);
}
