#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Item {
    std::string name;
    std::string description;

public:
    Item(std::string name, std::string description)
        : name(std::move(name)), description(std::move(description)) {}

    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
};

class Room {
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<Item>> items;

public:
    Room(std::string name, std::string description)
        : name(std::move(name)), description(std::move(description)) {}

    void addItem(std::shared_ptr<Item> item) {
        items.push_back(item);
    }

   
};

class Player {
    std::string name;
    std::vector<std::shared_ptr<Item>> inventory;

public:
    Player(std::string name) : name(std::move(name)) {}

    void addItemToInventory(std::shared_ptr<Item> item) {
        inventory.push_back(item);
    }

   
};


class Puzzle {
    std::string description;
    bool isSolved;

public:
    Puzzle(std::string description)
        : description(std::move(description)), isSolved(false) {}

    virtual bool solve(const std::string& solution) {
      
        isSolved = true; 
        return isSolved;
    }
};

class Interaction {
 
};

class GameEngine {
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;
    std::unique_ptr<Player> player;

public:
    GameEngine() : player(std::make_unique<Player>("Default Player")) {}

    void addRoom(std::shared_ptr<Room> room) {
        rooms[room->name] = room;
    }

    
};



int main() {
    GameEngine game;

   
    auto room1 = std::make_shared<Room>("Entrance Hall", "A large hall with a marble floor.");
    auto room2 = std::make_shared<Room>("Library", "A quiet, dusty library filled with books.");
    game.addRoom(room1);
    game.addRoom(room2);


    room1->addItem(std::make_shared<Item>("Key", "A small rusty key."));
    room2->addItem(std::make_shared<Item>("Book", "An ancient book with mysterious inscriptions."));


    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        }

      
    }

    return 0;
}




