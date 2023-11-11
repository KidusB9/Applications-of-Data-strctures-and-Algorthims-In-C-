#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Character;
class Item;

// Abstract class for items
class Item {
public:
    std::string name;
    int power;

    Item(std::string name, int power) : name(std::move(name)), power(power) {}

    virtual void use(Character& character) = 0;
};

// Abstract class for characters
class Character {
protected:
    std::string name;
    int health;
    std::vector<std::unique_ptr<Item>> inventory;

public:
    Character(std::string name, int health) : name(std::move(name)), health(health) {}

    virtual void attack(Character& target) = 0;
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
    }

    void addItem(std::unique_ptr<Item> item) {
        inventory.push_back(std::move(item));
    }

    void useItem(const std::string& itemName, Character& target) {
        for (auto& item : inventory) {
            if (item->name == itemName) {
                item->use(target);
                break;
            }
        }
    }

    bool isAlive() const { return health > 0; }
    const std::string& getName() const { return name; }
};

// Concrete item class
class Potion : public Item {
public:
    Potion() : Item("Health Potion", 50) {}

    void use(Character& character) override {
        std::cout << character.getName() << " uses " << name << ". Restores " << power << " health.\n";
        character.takeDamage(-power); // Negative damage to heal
    }
};

// Concrete character class
class Warrior : public Character {
public:
    Warrior(std::string name) : Character(std::move(name), 100) {}

    void attack(Character& target) override {
        int damage = 10; // Basic attack damage
        std::cout << name << " attacks " << target.getName() << " for " << damage << " damage.\n";
        target.takeDamage(damage);
    }
};

// Combat function
void combat(Character& character1, Character& character2) {
    while (character1.isAlive() && character2.isAlive()) {
        character1.attack(character2);
        if (character2.isAlive()) {
            character2.attack(character1);
        }
    }

    if (character1.isAlive()) {
        std::cout << character1.getName() << " wins!\n";
    } else {
        std::cout << character2.getName() << " wins!\n";
    }
}

// Main function
int main() {
    Warrior warrior1("Arthur");
    Warrior warrior2("Lancelot");

    // Add items to characters
    warrior1.addItem(std::make_unique<Potion>());
    warrior2.addItem(std::make_unique<Potion>());

    // Commence combat
    combat(warrior1, warrior2);

    return 0;
}
