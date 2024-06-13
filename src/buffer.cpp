#include "../include/buffer.h"
#include "../include/editor.h"

Buffer::Buffer() {
    clip = nullptr; // buffer text
}

char* Buffer::getClip() {
    return clip;
}


void Buffer::cut(CommandsLog* cmdLog, Cursor c, size_t length) {
    copy(c, length);
    Editor::deleteText(cmdLog, c, length);
}

void Buffer::copy(Cursor c, size_t length) {
    Line* line = c.getCursorLine();
    int charIndex = c.getCursorCharIndex();
    delete[] clip; // deallocate to avoid a memory leak
    clip = new char[length + 1];
    std::copy(line->text + charIndex, line->text + charIndex + length, clip);
    clip[length] = '\0'; // null-terminate the string
}

void Buffer::paste(CommandsLog* cmdLog, Cursor c) {
    if (clip)
        Editor::insertText(cmdLog, c, clip);
}
