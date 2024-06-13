#include <iostream>
#include "../include/application.h"
#include "../include/file_handler.h"

void Application::printCommandsInfo() {
    std::cout << "0 - Help\n"
              << "1 - Set cursor\n"
              << "2 - Print current text\n"
              << "3 - New line\n"
              << "4 - Append to the end\n"
              << "5 - Insert by line and index\n"
              << "6 - Replace by line and index\n"
              << "7 - Delete by line and index\n"
              << "8 - Cut\n"
              << "9 - Copy\n"
              << "10 - Paste\n"
              << "11 - Search\n"
              << "12 - Save into the file\n"
              << "13 - Load from the file\n"
              << "14 - Undo\n"
              << "15 - Redo\n"
              << "16 - Exit\n";
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
            cursor.setCursor(&content, Parser::readInteger("Enter a line index: "), Parser::readInteger("Enter a char index: "));
            return;
        case 2:
            Editor::printText(&content);
            return;
        case 3:
            Editor::newLine(&content, &cmdLog, Parser::readText());
            cursor.updateCursor(content.tail, content.length - 1, 0);
            return;
        case 4:
            Editor::appendText(&content, &cmdLog, Parser::readText());
            if (content.length == 1)
                cursor.updateCursor(content.tail, content.length - 1, 0);
            return;
        case 5:
            Editor::insertText(&cmdLog, cursor, Parser::readText());
            return;
        case 6:
            Editor::replaceText(&cmdLog, cursor, Parser::readText());
            return;
        case 7:
            Editor::deleteText(&cmdLog, cursor, Parser::readInteger("Enter a length to delete: "));
            return;
        case 8:
            buffer.cut(&cmdLog, cursor, Parser::readInteger("Enter a length to cut: "));
            return;
        case 9:
            buffer.copy(cursor, Parser::readInteger("Enter a length to copy: "));
            return;
        case 10:
            buffer.paste(&cmdLog, cursor);
            return;
        case 11:
            Editor::search(&content, Parser::readText());
            return;
        case 12:
            FileHandler::saveToFile(&content,Parser::readText());
            return;
        case 13:
            FileHandler::loadFromFile(&content, &cmdLog, Parser::readText());
            return;
        case 14:
            cmdLog.undo(&content, cursor);
            return;
        case 15:
            cmdLog.redo(&content, cursor);
            return;
        case 16: // Exit
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
    } while (command != 16);  // 8 - exit command
}
