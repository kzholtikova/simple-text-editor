#include <iostream>
#include "../include/application.h"
#include "../include/file_handler.h"

void Application::printCommandsInfo() {
    std::cout << "0 - Help\n"
              << "1 - Append to the end\n"
              << "2 - New line\n"
              << "3 - Save into the file\n"
              << "4 - Load from the file\n"
              << "5 - Print current text\n"
              << "6 - Insert by line and index\n"
              << "7 - Replace by line and index\n"
              << "8 - Delete by line and index\n"
              << "9 - Search\n"
              << "10 - Cut\n"
              << "11 - Copy\n"
              << "12 - Paste\n"
              << "13 - Undo\n"
              << "14 - Redo\n"
              << "15 - Exit\n";
}

void  Application::clearConsole() {
    std::cout << "\e[1;1H\e[2J"; // RegEx using ANSI escape codes
}

// Call the function related to the command number
void  Application::executeCommand() {
    switch (command) {
        case 0: // Help
            printCommandsInfo();
            return;
        case 1:
            Editor::appendText(&content, &cmdLog, Parser::readText());
            return;
        case 2:
            Editor::newLine(&content, &cmdLog, Parser::readText());
            return;
        case 3:
            FileHandler::saveToFile(&content,Parser::readText());
            return;
        case 4:
            FileHandler::loadFromFile(&content, &cmdLog, Parser::readText());
            return;
        case 5:
            Editor::printText(&content);
            return;
        case 6:
            Editor::insertBy(&content, &cmdLog,Parser::readInteger("Enter a line index: "),
                             Parser::readInteger("Enter a char index: "), Parser::readText());
            return;
        case 7:
            Editor::replaceBy(&content, &cmdLog, Parser::readInteger("Enter a line index: "),
                              Parser::readInteger("Enter a char index: "), Parser::readText());
            return;
        case 8:
            Editor::deleteBy(&content, &cmdLog, Parser::readInteger("Enter a line index: "),
                             Parser::readInteger("Enter a char index: "),
                             Parser::readInteger("Enter a length: "));
            return;
        case 9:
            Editor::search(&content, Parser::readText());
            return;
        case 10:
            buffer.cut(&content, &cmdLog, Parser::readInteger("Enter a line index: "),
                        Parser::readInteger("Enter a char index: "),
                        Parser::readInteger("Enter a length: "));
            return;
        case 11:
            buffer.copy(&content, Parser::readInteger("Enter a line index: "),
                         Parser::readInteger("Enter a char index: "),
                         Parser::readInteger("Enter a length: "));
            return;
        case 12:
            buffer.paste(&content, &cmdLog, Parser::readInteger("Enter a line index: "),
                          Parser::readInteger("Enter a char index: "));
            return;
        case 13:
            cmdLog.undo(&content);
            return;
        case 14:
            cmdLog.redo(&content);
            return;
        case 15: // Exit
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
    } while (command != 15);  // 8 - exit command
}
