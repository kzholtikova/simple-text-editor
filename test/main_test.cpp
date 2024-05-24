#include <gtest/gtest.h>
#include "../include/parser.h"
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

int original_stdout;

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

// Utility function to capture stdout
std::string captureStdout(void (*func)(LinkedList*), LinkedList* list) {
    int original_stdout = dup(fileno(stdout));
    freopen("output.txt", "w", stdout);
    func(list);
    fflush(stdout);  // Ensure all output is flushed
    dup2(original_stdout, fileno(stdout));  // Reset stdout
    close(original_stdout);

    std::ifstream output_file("output.txt");
    std::stringstream buffer;
    buffer << output_file.rdbuf();
    output_file.close();
    remove("output.txt");

    return buffer.str();
}

// Utility function to redirect stdout to a file
void redirectStdout() {
    original_stdout = dup(fileno(stdout));
    freopen("stdout.txt", "w", stdout);
}

// Utility function to reset stdoutvoid
void resetStdout() {
    fflush(stdout);
    dup2(original_stdout, fileno(stdout));
    close(original_stdout);
    remove("stdout.txt");
}
