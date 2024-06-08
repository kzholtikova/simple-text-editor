#include <fstream>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::streambuf* redirectCout() {
    std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); // save old buf
    std::cout.rdbuf(out.rdbuf()); // redirect std::cout to output.txt
    return coutbuf;
}

void resetCout(std::streambuf* coutbuf) {
    std::cout.rdbuf(coutbuf);
}
