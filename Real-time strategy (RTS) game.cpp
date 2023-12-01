#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <map>

// Forward declarations
class Unit;
class GameMap;

enum class TerrainType { Grass, Water, Mountain };

class Terrain {
    TerrainType type;
public:
    Terrain(TerrainType type) : type(type) {}

    TerrainType getType() const {
        return type;
    }

    char getSymbol() const {
        switch (type) {
            case TerrainType::Grass: return '.';
            case TerrainType::Water: return '~';
            case TerrainType::Mountain: return '^';
            default: return '?';
        }
    }
};

class GameMap {
    int width, height;
    std::vector<std::vector<Terrain>> map;

public:
    GameMap(int width, int height) : width(width), height(height), map(height, std::vector<Terrain>(width, Terrain(TerrainType::Grass))) {}

    void generateRandomTerrain() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);

        for (auto& row : map) {
            for (auto& cell : row) {
                cell = Terrain(static_cast<TerrainType>(dis(gen)));
            }
        }
    }

    void display() const {
        for (const auto& row : map) {
            for (const auto& cell : row) {
                std::cout << cell.getSymbol() << ' ';
            }
            std::cout << '\n';
        }
    }

  
};


enum class UnitType { Infantry, Tank, Artillery };

class Unit {
    std::string name;
    UnitType type;
    int health;
    int attackPower;
   

public:
    Unit(std::string name, UnitType type, int health, int attackPower)
        : name(std::move(name)), type(type), health(health), attackPower(attackPower) {}

    void attack(Unit& target) {
     
        std::cout << name << " attacks " << target.name << " for " << attackPower << " damage!" << std::endl;
        target.health -= attackPower;
    }

    
};

class RTSGame {
    GameMap gameMap;
    std::vector<std::unique_ptr<Unit>> units;
  

public:
    RTSGame(int width, int height) : gameMap(width, height) {
        gameMap.generateRandomTerrain();
    }

    void addUnit(const std::string& name, UnitType type, int health, int attackPower) {
        units.emplace_back(std::make_unique<Unit>(name, type, health, attackPower));
    }

    void run() {
  
        gameMap.display();
        // Simulate some game actions
    }

  
};

int main() {
    RTSGame game(10, 10);
    game.addUnit("Infantry", UnitType::Infantry, 100, 10);
    game.addUnit("Tank", UnitType::Tank, 150, 20);
    game.run();

    return 0;
}

