#include "../include/buffer.h"
#include "../include/editor.h"

Buffer::Buffer(CommandsLog& cmdLog) : cmdLog(cmdLog) {
    //  ref members must be initialized in the initializer list, not in the constructor body
    clip = nullptr; // buffer text
}

char* Buffer::getClip() {
    return clip;
}


void Buffer::cut(Editor editor, int lineIndex, int charIndex, size_t length) {
    copy(editor, lineIndex, charIndex, length);
    editor.deleteBy(lineIndex, charIndex, length);
}

void Buffer::copy(Editor editor, int lineIndex, int charIndex, size_t length) {
    Line *line = editor.setPosition(lineIndex, charIndex);
    if (line) {
        if (clip)
            delete[] clip; // deallocate to avoid a memory leak
        clip = new char[length + 1];
        std::copy(line->text + charIndex, line->text + charIndex + length, clip);
        clip[length] = '\0'; // null-terminate the string
    }
}

void Buffer::paste(Editor editor, int lineIndex, int charIndex) {
    if (clip)
        editor.insertBy(lineIndex, charIndex, clip);
}
