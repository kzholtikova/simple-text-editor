#include <gtest/gtest.h>
#include "../include/caesar_cipher.h"
#include "../include/editor.h"

TEST(CaesarCipherTest, EncryptTextWithPositiveKey) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 3);
    EXPECT_STREQ(content->head->text, "khoor!");
}

TEST(CaesarCipherTest, EncryptTextWithZeroKey) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 0);
    EXPECT_STREQ(content->head->text, "hello!");
}

TEST(CaesarCipherTest, DecryptText) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "khoor!");
    cipher.decryptText(content, 3);
    EXPECT_STREQ(content->head->text, "hello!");
}

TEST(CaesarCipherTest, EncryptTextWithEmptyString) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    cipher.encryptText(content, 3);
    EXPECT_EQ(content->head, nullptr);
}

TEST(CaesarCipherTest, EncryptTextWithMultipleLines) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "line1,");
    Editor::newLine(content, nullptr, "line2;");
    Editor::newLine(content, nullptr, "line3.");
    cipher.encryptText(content, 28);
    EXPECT_STREQ(content->head->text, "nkpg1,");
    EXPECT_STREQ(content->head->next->text, "nkpg2;");
    EXPECT_STREQ(content->tail->text, "nkpg3.");
}

TEST(CaesarCipherTest, EncryptAndDecryptText) {
    CaesarCipher cipher;
    auto* content = new LinkedList();
    Editor::newLine(content, nullptr, "hello!");
    cipher.encryptText(content, 3);
    cipher.decryptText(content, 3);
    EXPECT_STREQ(content->head->text, "hello!");
}
