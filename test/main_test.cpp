#include <fstream>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::streambuf* redirectCin() {
    static std::stringstream testInput;  // Make it static to ensure it stays in scope
    testInput.str("");  // Clear the stringstream
    testInput.clear();  // Clear any error flags
    testInput << "\n";  // Provide a newline character as input
    // Save the old buffer and redirect std::cin to read from testInput
    std::streambuf *oldCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(testInput.rdbuf());
    return oldCinBuffer;
}

void resetCin(std::streambuf* cinBuffer) {
    std::cin.rdbuf(cinBuffer);
}

std::streambuf* redirectCout() {
    static std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); // save old buf
    std::cout.rdbuf(out.rdbuf()); // redirect std::cout to output.txt
    return coutbuf;
}

void resetCout(std::streambuf* coutbuf) {
    std::cout.rdbuf(coutbuf);
}
