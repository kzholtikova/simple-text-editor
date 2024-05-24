#include <gtest/gtest.h>
#include "../include/parser.h"
#include <fstream>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Utility function to redirect stdin from a string
void setInput(const std::string& input) {
    std::ofstream input_file("input.txt");
    input_file << input;
    input_file.close();
    freopen("input.txt", "r", stdin);
}

// Utility function to reset stdin
void resetInput() {
    freopen("/dev/tty", "r", stdin);  // Reset stdin
    remove("input.txt");
}

// Utility function to capture stdout
std::string captureStdout(void (*func)(LinkedList*), LinkedList* list) {
    freopen("output.txt", "w", stdout);
    func(list);
    fflush(stdout);  // Ensure all output is flushed
    freopen("/dev/tty", "w", stdout);  // Reset stdout

    std::ifstream output_file("output.txt");
    std::stringstream buffer;
    buffer << output_file.rdbuf();
    output_file.close();
    remove("output.txt");

    return buffer.str();
}

// Utility function to redirect stdout to a file
void redirectStdout() {
    freopen("stdout.txt", "w", stdout);
}

// Utility function to reset stdout
void resetStdout() {
    freopen("/dev/tty", "w", stdout);
    remove("stdout.txt");
}
