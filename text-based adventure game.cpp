#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Forward declarations
class Room;
class Player;

// Class representing a room in the game
class Room {
    std::string description;
    std::unordered_map<std::string, Room*> exits;

public:
    Room(const std::string& desc) : description(desc) {}

    void setExit(const std::string& direction, Room* room) {
        exits[direction] = room;
    }

    Room* getExit(const std::string& direction) const {
        auto it = exits.find(direction);
        return it != exits.end() ? it->second : nullptr;
    }

    const std::string& getDescription() const {
        return description;
    }
};

// Class representing the player
class Player {
    std::string name;
    Room* currentRoom;

public:
    Player(const std::string& name, Room* startRoom) : name(name), currentRoom(startRoom) {}

    void move(const std::string& direction) {
        Room* nextRoom = currentRoom->getExit(direction);
        if (nextRoom) {
            currentRoom = nextRoom;
            std::cout << "You go " << direction << " and find yourself in " << currentRoom->getDescription() << std::endl;
        } else {
            std::cout << "There is no way to go " << direction << " from here." << std::endl;
        }
    }
};

// Game setup and main loop
int main() {
    // Create rooms
    Room livingRoom("a cozy living room");
    Room kitchen("a kitchen with a shiny metal sink");
    Room garden("a beautiful garden");

    // Set exits
    livingRoom.setExit("north", &kitchen);
    kitchen.setExit("south", &livingRoom);
    kitchen.setExit("east", &garden);
    garden.setExit("west", &kitchen);

    // Create player
    Player player("Adventurer", &livingRoom);

    // Game loop
    std::string command;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        } else if (command == "look") {
            std::cout << "You are in " << player.currentRoom->getDescription() << std::endl;
        } else if (command == "north" || command == "south" || command == "east" || command == "west") {
            player.move(command);
        } else {
            std::cout << "I don't understand that command." << std::endl;
        }
    }

    std::cout << "Thank you for playing!" << std::endl;
    return 0;
}
