#include <gtest/gtest.h>
#include <fstream>
#include "../include/caesar_cipher.h"
#include "../include/editor.h"
#include "main_test.h"

TEST(CaesarCipherTest, EncryptDecryptText) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 3);
    EXPECT_STREQ(content->head->text, "khoor!");
    cipher.decryptText(content, 3);
    EXPECT_STREQ(content->head->text, "hello!");
    delete content;
}

TEST(CaesarCipherTest, EncryptDecryptMultipleLines) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "line1,");
    Editor::newLine(content, nullptr, "line2;");
    Editor::newLine(content, nullptr, "line3.");
    cipher.encryptText(content, 2);
    EXPECT_STREQ(content->head->text, "nkpg1,");
    EXPECT_STREQ(content->head->next->text, "nkpg2;");
    EXPECT_STREQ(content->tail->text, "nkpg3.");
    cipher.decryptText(content, 2);
    EXPECT_STREQ(content->head->text, "line1,");
    EXPECT_STREQ(content->head->next->text, "line2;");
    EXPECT_STREQ(content->tail->text, "line3.");
}

TEST(CaesarCipherTest, EncryptDecryptEmptyText) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "");
    cipher.encryptText(content, 3);
    EXPECT_STREQ(content->head->text, "");
    cipher.decryptText(content, 3);
    EXPECT_STREQ(content->head->text, "");
    delete content;
}

TEST(CaesarCipherTest, EncryptDecryptTextWithZeroKey) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 0);
    EXPECT_STREQ(content->head->text, "hello!");
    cipher.decryptText(content, 0);
    EXPECT_STREQ(content->head->text, "hello!");
    delete content;
}

TEST(CaesarCipherTest, EncryptDecryptTextWithBigKey) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 55);
    EXPECT_STREQ(content->head->text, "khoor!");
    cipher.decryptText(content, 55);
    EXPECT_STREQ(content->head->text, "hello!");
    delete content;
}

TEST(CaesarCipherTest, EncryptDecryptFile) {
    CaesarCipher cipher;
    const char* filename = "test.txt";
    std::ofstream file(filename);
    file << "hello!";
    file.close();
    cipher.encryptFile(filename, 3);
    cipher.decryptFile(filename, 3);
    std::ifstream inFile(filename);
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    EXPECT_STREQ(content.c_str(), "hello!");
}

TEST(CaesarCipherTest, EncryptDecryptEmptyFile) {
    CaesarCipher cipher;
    const char* filename = "test.txt";
    std::ofstream file(filename);
    file << "";
    file.close();
    cipher.encryptFile(filename, 3);
    cipher.decryptFile(filename, 3);
    std::ifstream inFile(filename);
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    EXPECT_STREQ(content.c_str(), "");
}

TEST(CaesarCipherTest, EncryptDecryptNonExistingFile) {
    CaesarCipher cipher;
    std::streambuf* cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    cipher.encryptFile("not_a_file", 3);
    std::string outputEnc = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(outputEnc, "Error opening file: not_a_file\n");
    cinbuf = redirectCin();
    testing::internal::CaptureStderr();
    cipher.decryptFile("not_a_file", 3);
    std::string outputDec = testing::internal::GetCapturedStderr();
    resetCin(cinbuf);
    EXPECT_EQ(outputDec, "Error opening file: not_a_file\n");
}