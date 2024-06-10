#pragma once
#include <functional>

class Command {
public:
    std::function<void()> execute;
    std::function<void()> unexecute;

    Command() {} // Default constructor
    Command(std::function<void()> execute, std::function<void()> unexecute) : execute(execute), unexecute(unexecute) {}
};

class CommandsLog {
private:
    Command* stack;
    Command* stackPtr;
    size_t stackSize;

public:
    CommandsLog();

    void undo();
    void redo();

    void log(Command cmd);
};
