#include <iostream>
#include "../include/application.h"
#include "../include/edit_commands.h"
#include "../include/file_commands.h"

void Application::printCommandsInfo() {
    std::cout << "0 - Help\n"
              << "1 - Append to the end\n"
              << "2 - New line\n"
              << "3 - Save into the file\n"
              << "4 - Load from the file\n"
              << "5 - Print current text\n"
              << "6 - Insert by line and index\n"
              << "7 - Search\n"
              << "8 - Exit\n";
}

void  Application::clearConsole() {
    std::cout << "\e[1;1H\e[2J"; // RegEx using ANSI escape codes
}

// Call the function related to the command number
void  Application::executeCommand() {
    switch (command) {
        case 0:
            printCommandsInfo();
            return;
        case 1:
            Editor::appendText(content, Parser::readText());
            return;
        case 2:
            Editor::newLine(content, Parser::readText());
            return;
        case 3:
            FileHandler::saveToFile(content, Parser::readText());
            return;
        case 4:
            FileHandler::loadFromFile(content, Parser::readText());
            return;
        case 5:
            Editor::printText(content);
            return;
        case 6:
            Editor::insertBy(content, Parser::readInteger("Enter a line index: "),
                             Parser::readInteger("Enter a char index: "), Parser::readText());
            return;
        case 7:
            Editor::search(content, Parser::readText());
            return;
        case 8: // Exit
            std::cout << "Bye!";
            return;
        default:
            std::cout << "No such command.\n";
            printCommandsInfo();
            return;
    }
}

void Application::run() {
    do {
        command = Parser::readInteger("Choose a command (0-8): ");
        clearConsole();
        executeCommand();
    } while (command != 8);  // 8 - exit command
}
