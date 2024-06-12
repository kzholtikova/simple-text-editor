#include "../include/buffer.h"
#include "../include/editor.h"

Buffer::Buffer() {
    clip = nullptr; // buffer text
}

char* Buffer::getClip() {
    return clip;
}


void Buffer::cut(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex, size_t length) {
    copy(content, lineIndex, charIndex, length);
    Editor::deleteBy(content, cmdLog, lineIndex, charIndex, length);
}

void Buffer::copy(LinkedList* content, int lineIndex, int charIndex, size_t length) {
    Line *line = Editor::setPosition(content, lineIndex, charIndex);
    if (line) {
        delete[] clip; // deallocate to avoid a memory leak
        clip = new char[length + 1];
        std::copy(line->text + charIndex, line->text + charIndex + length, clip);
        clip[length] = '\0'; // null-terminate the string
    }
}

void Buffer::paste(LinkedList* content, CommandsLog* cmdLog, int lineIndex, int charIndex) {
    if (clip)
        Editor::insertBy(content, cmdLog,  lineIndex, charIndex, clip);
}
