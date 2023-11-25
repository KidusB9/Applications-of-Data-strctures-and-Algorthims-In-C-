#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <map>

// Forward declarations
class Character;
class Enemy;
class Location;

// Base class for all characters in the game
class Character {
protected:
    std::string name;
    int health;
    int strength;
    int level;

public:
    Character(std::string name, int health, int strength, int level)
        : name(std::move(name)), health(health), strength(strength), level(level) {}

    virtual void attack(Character& target) {
        int damage = strength * level;
        std::cout << name << " attacks " << target.name << " for " << damage << " damage!" << std::endl;
        target.takeDamage(damage);
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << " has " << health << " health remaining." << std::endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    const std::string& getName() const {
        return name;
    }

    virtual void levelUp() {
        level++;
        health += 10;
        strength += 5;
        std::cout << name << " has leveled up to level " << level << "!" << std::endl;
    }
};

// Enemy class
class Enemy : public Character {
public:
    Enemy(std::string name, int health, int strength, int level)
        : Character(std::move(name), health, strength, level) {}

    void levelUp() override {
        // Specific logic for leveling up an enemy
        Character::levelUp(); // Call base class implementation
    }
};

// Player class
class Player : public Character {
public:
    Player(std::string name)
        : Character(std::move(name), 100, 10, 1) {}

    void levelUp() override {
        // Specific logic for leveling up the player
        Character::levelUp(); // Call base class implementation
    }
};

// Location class
class Location {
    std::string name;
    std::vector<std::shared_ptr<Enemy>> enemies;

public:
    Location(std::string name) : name(std::move(name)) {}

    void addEnemy(std::shared_ptr<Enemy> enemy) {
        enemies.push_back(std::move(enemy));
    }

    void enter(Player& player) {
        std::cout << player.getName() << " enters " << name << std::endl;
        for (auto& enemy : enemies) {
            while (player.isAlive() && enemy->isAlive()) {
                player.attack(*enemy);
                if (enemy->isAlive()) {
                    enemy->attack(player);
                }
            }

            if (!player.isAlive()) {
                std::cout << player.getName() << " has been defeated!" << std::endl;
                return;
            } else {
                std::cout << enemy->getName() << " has been defeated!" << std::endl;
                player.levelUp();
            }
        }
    }
};

int main() {
    Player player("Hero");

    Location forest("Enchanted Forest");
    forest.addEnemy(std::make_shared<Enemy>("Goblin", 30, 5, 1));
    forest.addEnemy(std::make_shared<Enemy>("Troll", 50, 10, 2));

    forest.enter(player);

    return 0;
}
