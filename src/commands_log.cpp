#include<iostream>
#include "../include/commands_log.h"

CommandsLog::CommandsLog() {
    stack = new Command[4];
    stackPtr = stack;
    stackSize = 4;
}

void CommandsLog::log(Command cmd) {
    if (stackPtr - stack == stackSize) {
        stackSize *= 2;
        Command* newStack = new Command[stackSize];
        std::copy(stack, stackPtr, newStack);
        delete[] stack;
        stack = newStack;
        stackPtr = stack + stackSize / 2;
    }

    stackPtr++;
    *stackPtr = cmd;
}

void CommandsLog::undo() {

}

void CommandsLog::redo() {

}


