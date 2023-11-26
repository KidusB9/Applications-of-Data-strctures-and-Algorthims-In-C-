#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#

class TextEditor {
    std::string buffer;

public:
    void write(const std::string& text) {
        buffer += text;
    }

    bool saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        file << buffer;
        file.close();
        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        std::stringstream ss;
        ss << file.rdbuf();
        buffer = ss.str();
        file.close();
        return true;
    }

    void display() const {
        std::cout << buffer << std::endl;
    }
};

int main() {
    TextEditor editor;
    std::string command;

    while (true) {
        std::cout << "Enter command (write, save, load, display, quit): ";
        std::getline(std::cin, command);

        if (command == "write") {
            std::cout << "Enter text: ";
            std::string text;
            std::getline(std::cin, text);
            editor.write(text);
        } else if (command == "save") {
            std::cout << "Enter filename: ";
            std::string filename;
            std::getline(std::cin, filename);
            if (!editor.saveToFile(filename)) {
                std::cerr << "Error saving file." << std::endl;
            }
        } else if (command == "load") {
            std::cout << "Enter filename: ";
            std::string filename;
            std::getline(std::cin, filename);
            if (!editor.loadFromFile(filename)) {
                std::cerr << "Error loading file." << std::endl;
            }
        } else if (command == "display") {
            editor.display();
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
