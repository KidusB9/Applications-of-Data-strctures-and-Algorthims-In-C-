#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>

// Forward declarations
class Creature;
class Ecosystem;

// Vector2D for spatial coordinates
struct Vector2D {
    float x, y;

    Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // Vector operations can be added here (addition, subtraction, normalization, etc.)
};

// Abstract class representing a creature in the ecosystem
class Creature {
protected:
    Vector2D position;
    float health;
    std::string type;

public:
    Creature(const std::string& type, const Vector2D& pos) : type(type), position(pos), health(100.0f) {}

    virtual void update(Ecosystem& ecosystem) = 0;

    const Vector2D& getPosition() const { return position; }
    const std::string& getType() const { return type; }
};

// Concrete creature classes
class Herbivore : public Creature {
public:
    Herbivore(const Vector2D& pos) : Creature("Herbivore", pos) {}

    void update(Ecosystem& ecosystem) override {
        // Implement behavior for moving, eating, etc.
    }
};

class Carnivore : public Creature {
public:
    Carnivore(const Vector2D& pos) : Creature("Carnivore", pos) {}

    void update(Ecosystem& ecosystem) override {
        // Implement behavior for hunting, eating, etc.
    }
};

// The Ecosystem class that manages all creatures
class Ecosystem {
    std::vector<std::unique_ptr<Creature>> creatures;

public:
    void addCreature(std::unique_ptr<Creature> creature) {
        creatures.push_back(std::move(creature));
    }

    void update() {
        for (auto& creature : creatures) {
            creature->update(*this);
        }
        // Additional logic to handle creature interactions, removal of dead creatures, etc.
    }

    void display() const {
        for (const auto& creature : creatures) {
            std::cout << creature->getType() << " at (" << creature->getPosition().x << ", " << creature->getPosition().y << ")\n";
        }
    }

    // Additional methods can be added to manage the ecosystem
};

int main() {
    Ecosystem ecosystem;
    ecosystem.addCreature(std::make_unique<Herbivore>(Vector2D(10.0f, 20.0f)));
    ecosystem.addCreature(std::make_unique<Carnivore>(Vector2D(15.0f, 25.0f)));

    for (int day = 0; day < 10; ++day) {
        std::cout << "Day " << day + 1 << std::endl;
        ecosystem.update();
        ecosystem.display();
        std::cout << std::endl;
    }

    return 0;
}
