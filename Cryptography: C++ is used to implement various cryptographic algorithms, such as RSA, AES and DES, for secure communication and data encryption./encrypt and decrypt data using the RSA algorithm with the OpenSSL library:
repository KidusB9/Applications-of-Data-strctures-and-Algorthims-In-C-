#include <openssl/aes.h>
#include <iostream>
#include <string>

std::string encrypt(const std::string &plaintext, const std::string &key) {
    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)key.c_str(), 128, &aes_key);

    std::string ciphertext(plaintext.size(), 0);
    AES_encrypt((const unsigned char *)plaintext.c_str(), (unsigned char *)ciphertext.c_str(), &aes_key);

    return ciphertext;
}

std::string decrypt(const std::string &ciphertext, const std::string &key) {
    AES_KEY aes_key;
    AES_set_decrypt_key((const unsigned char *)key.c_str(), 128, &aes_key);

    std::string plaintext(ciphertext.size(), 0);
    AES_decrypt((const unsigned char *)ciphertext.c_str(), (unsigned char *)plaintext.c_str(), &aes_key);

    return plaintext;
}

int main() {
    std::string plaintext = "This is a secret message.";
    std::string key = "0123456789abcdef";

    std::string ciphertext = encrypt(plaintext, key);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    std::string decrypted = decrypt(ciphertext, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
