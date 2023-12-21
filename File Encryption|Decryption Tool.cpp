#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class FileEncryptor {
    std::string key;

    std::string generateKeystream(size_t length) {
        std::string keystream;
        for (size_t i = 0, j = 0; i < length; ++i, j = (j + 1) % key.length()) {
            keystream += key[j];
        }
        return keystream;
    }

public:
    FileEncryptor(std::string key) : key(std::move(key)) {
        if (this->key.empty()) {
            throw std::invalid_argument("Key cannot be empty");
        }
    }

    void processFile(const std::string& inputFilePath, const std::string& outputFilePath, bool encrypt) {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        std::ofstream outputFile(outputFilePath, std::ios::binary);

        if (!inputFile.is_open() || !outputFile.is_open()) {
            throw std::runtime_error("Error opening files");
        }

        std::string keystream = generateKeystream(fs::file_size(inputFilePath));
        char ch;
        size_t keystreamIndex = 0;

        while (inputFile.get(ch)) {
            char processedChar = encrypt ? (ch ^ keystream[keystreamIndex++]) : (ch ^ keystream[keystreamIndex++]);
            outputFile.put(processedChar);
        }
    }

    void encryptFile(const std::string& inputFilePath, const std::string& outputFilePath) {
        processFile(inputFilePath, outputFilePath, true);
    }

    void decryptFile(const std::string& inputFilePath, const std::string& outputFilePath) {
        processFile(inputFilePath, outputFilePath, false);
    }
};

void showUsage() {
    std::cout << "Usage:\n"
              << "  encrypt <key> <input_file> <output_file>\n"
              << "  decrypt <key> <input_file> <output_file>\n";
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        showUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string key = argv[2];
    std::string inputFile = argv[3];
    std::string outputFile = argv[4];

    try {
        FileEncryptor encryptor(key);
        
        if (command == "encrypt") {
            encryptor.encryptFile(inputFile, outputFile);
            std::cout << "File encrypted successfully." << std::endl;
        } else if (command == "decrypt") {
            encryptor.decryptFile(inputFile, outputFile);
            std::cout << "File decrypted successfully." << std::endl;
        } else {
            showUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
