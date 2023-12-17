#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class TextAnalyzer {
public:
    void analyzeFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        std::unordered_map<std::string, int> wordCount;
        int sentenceCount = 0, wordTotal = 0;
        std::string line, word;

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            while (std::getline(lineStream, word, ' ')) {
                if (!word.empty()) {
                    wordCount[word]++;
                    wordTotal++;
                }
            }
            sentenceCount += countSentences(line);
        }

        file.close();

        displayStatistics(wordCount, sentenceCount, wordTotal);
    }

private:
    int countSentences(const std::string& line) {
        int count = 0;
        for (char ch : line) {
            if (ch == '.' || ch == '?' || ch == '!') {
                count++;
            }
        }
        return count;
    }

    void displayStatistics(const std::unordered_map<std::string, int>& wordCount,
                           int sentenceCount, int wordTotal) const {
        std::cout << "Text Statistics:\n";
        std::cout << "Total words: " << wordTotal << "\n";
        std::cout << "Total sentences: " << sentenceCount << "\n";
        std::cout << "Word frequency:\n";
        for (const auto& pair : wordCount) {
            std::cout << "  " << pair.first << ": " << pair.second << "\n";
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    TextAnalyzer analyzer;
    analyzer.analyzeFile(argv[1]);

    return 0;
}
