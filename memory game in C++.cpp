#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <utility>

class MemoryGame {
    int size;
    std::vector<int> grid;
    std::vector<bool> revealed;

    void generateGrid() {
        for (int i = 1; i <= size * size / 2; ++i) {
            grid.push_back(i);
            grid.push_back(i);
        }
        std::random_shuffle(grid.begin(), grid.end());
    }

public:
    MemoryGame(int size) : size(size) {
        if (size % 2 != 0) {
            throw std::invalid_argument("Size must be even");
        }
        generateGrid();
        revealed.resize(size * size, false);
    }

    void displayGrid() {
        for (int i = 0; i < size * size; ++i) {
            if (revealed[i]) {
                std::cout << grid[i] << " ";
            } else {
                std::cout << "* ";
            }
            if ((i + 1) % size == 0) {
                std::cout << std::endl;
            }
        }
    }

    bool reveal(int pos1, int pos2) {
        if (pos1 < 0 || pos1 >= size * size || pos2 < 0 || pos2 >= size * size) {
            return false;
        }
        if (revealed[pos1] || revealed[pos2]) {
            return false;
        }

        revealed[pos1] = true;
        revealed[pos2] = true;

        displayGrid();

        if (grid[pos1] != grid[pos2]) {
            revealed[pos1] = false;
            revealed[pos2] = false;
            return false;
        }
        return true;
    }

    bool isCompleted() const {
        return std::all_of(revealed.begin(), revealed.end(), [](bool val) { return val; });
    }
};

int main() {
    MemoryGame game(4);

    while (!game.isCompleted()) {
        game.displayGrid();

        int choice1, choice2;
        std::cout << "Choose two numbers to reveal (0-15): ";
        std::cin >> choice1 >> choice2;

        if (!game.reveal(choice1, choice2)) {
            std::cout << "No match. Try again." << std::endl;
        }
    }

    std::cout << "Congratulations! You have completed the game." << std::endl;

    return 0;
}
