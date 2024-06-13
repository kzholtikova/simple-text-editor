#include <iostream>
#include "../include/application.h"
#include "../include/file_handler.h"

void Application::printCommandsInfo() {
    std::cout << "0 - Help\n"
              << "1 - Set cursor\n"
              << "2 - Move cursor right\n"
              << "3 - Move cursor left\n"
              << "5 - Print current text\n"
              << "6 - New line\n"
              << "6 - Append to the end\n"
              << "7 - Insert by line and index\n"
              << "8 - Replace by line and index\n"
              << "9 - Delete by line and index\n"
              << "10 - Cut\n"
              << "11 - Copy\n"
              << "12 - Paste\n"
              << "13 - Search\n"
              << "14 - Save into the file\n"
              << "15 - Load from the file\n"
              << "16 - Undo\n"
              << "17 - Redo\n"
              << "18 - Exit\n";
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
            cursor.moveCursorRight(Parser::readInteger("Enter a number of steps to right: "));
            return;
        case 3:
            cursor.moveCursorLeft(Parser::readInteger("Enter a number of steps to left: "));
            return;
        case 4:
            Editor::printText(&content);
            return;
        case 5:
            Editor::newLine(&content, &cmdLog, Parser::readText());
            cursor.updateCursor(content.tail, content.length - 1, 0);
            return;
        case 6:
            Editor::appendText(&content, &cmdLog, Parser::readText());
            if (content.length == 1)
                cursor.updateCursor(content.tail, content.length - 1, 0);
            return;
        case 7:
            Editor::insertText(&cmdLog, cursor, Parser::readText());
            return;
        case 8:
            Editor::replaceText(&cmdLog, cursor, Parser::readText());
            return;
        case 9:
            Editor::deleteText(&cmdLog, cursor, Parser::readInteger("Enter a length to delete: "));
            return;
        case 10:
            buffer.cut(&cmdLog, cursor, Parser::readInteger("Enter a length to cut: "));
            return;
        case 11:
            buffer.copy(cursor, Parser::readInteger("Enter a length to copy: "));
            return;
        case 12:
            buffer.paste(&cmdLog, cursor);
            return;
        case 13:
            Editor::search(&content, Parser::readText());
            return;
        case 14:
            FileHandler::saveToFile(&content,Parser::readText());
            return;
        case 15:
            FileHandler::loadFromFile(&content, &cmdLog, Parser::readText());
            return;
        case 16:
            cmdLog.undo(&content, cursor);
            return;
        case 17:
            cmdLog.redo(&content, cursor);
            return;
        case 18: // Exit
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
    } while (command != 18);  // exit command
}
