#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileManager {
public:
    void listDirectoryContents(const std::string& path) {
        if (!fs::exists(path) || !fs::is_directory(path)) {
            std::cerr << "Directory does not exist: " << path << std::endl;
            return;
        }

        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename().string();
            if (fs::is_directory(entry.path())) {
                std::cout << "/";
            }
            std::cout << std::endl;
        }
    }

    void createFile(const std::string& filePath) {
        std::ofstream file(filePath);
        if (!file) {
            std::cerr << "Failed to create file: " << filePath << std::endl;
        }
    }

    void createDirectory(const std::string& dirPath) {
        if (!fs::create_directories(dirPath)) {
            std::cerr << "Failed to create directory: " << dirPath << std::endl;
        }
    }

    void deleteFile(const std::string& filePath) {
        if (!fs::remove(filePath)) {
            std::cerr << "Failed to delete file: " << filePath << std::endl;
        }
    }

    void moveFile(const std::string& sourcePath, const std::string& destinationPath) {
        try {
            fs::rename(sourcePath, destinationPath);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Failed to move file: " << e.what() << std::endl;
        }
    }

    // Additional functionalities like copying files, reading file contents, etc., can be added here
};

void showUsage() {
    std::cout << "File Manager Usage:\n"
              << "  list <directory_path>\n"
              << "  create-file <file_path>\n"
              << "  create-dir <directory_path>\n"
              << "  delete <file_path>\n"
              << "  move <source_path> <destination_path>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        showUsage();
        return 1;
    }

    std::string command = argv[1];
    FileManager fileManager;

    if (command == "list") {
        fileManager.listDirectoryContents(argv[2]);
    } else if (command == "create-file") {
        fileManager.createFile(argv[2]);
    } else if (command == "create-dir") {
        fileManager.createDirectory(argv[2]);
    } else if (command == "delete") {
        fileManager.deleteFile(argv[2]);
    } else if (command == "move" && argc >= 4) {
        fileManager.moveFile(argv[2], argv[3]);
    } else {
        showUsage();
    }

    return 0;
}
