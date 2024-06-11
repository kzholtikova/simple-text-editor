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
            editor.appendText(Parser::readText());
            return;
        case 2:
            editor.newLine(Parser::readText());
            return;
        case 3:
            FileHandler::saveToFile(editor, Parser::readText());
            return;
        case 4:
            FileHandler::loadFromFile(editor,Parser::readText());
            return;
        case 5:
            editor.printText();
            return;
        case 6:
            editor.insertBy(Parser::readInteger("Enter a line index: "),
                             Parser::readInteger("Enter a char index: "), Parser::readText());
            return;
        case 7:
            editor.replaceBy(Parser::readInteger("Enter a line index: "),
                              Parser::readInteger("Enter a char index: "), Parser::readText());
            return;
        case 8:
            editor.deleteBy(Parser::readInteger("Enter a line index: "),
                             Parser::readInteger("Enter a char index: "),
                             Parser::readInteger("Enter a length: "));
            return;
        case 9:
            editor.search(Parser::readText());
            return;
        case 10:
            buffer.cut(editor, Parser::readInteger("Enter a line index: "),
                        Parser::readInteger("Enter a char index: "),
                        Parser::readInteger("Enter a length: "));
            return;
        case 11:
            buffer.copy(editor, Parser::readInteger("Enter a line index: "),
                         Parser::readInteger("Enter a char index: "),
                         Parser::readInteger("Enter a length: "));
            return;
        case 12:
            buffer.paste(editor, Parser::readInteger("Enter a line index: "),
                          Parser::readInteger("Enter a char index: "));
            return;
        case 13:
            cmdLog.undo();
            return;
        case 14:
            cmdLog.redo();
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
