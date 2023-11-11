#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <memory>

// 3D Vector Class
class Vec3 {
public:
    double x, y, z;

    Vec3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(double scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalized() const {
        double mag = magnitude();
        return Vec3(x / mag, y / mag, z / mag);
    }
};

// Particle Class
class Particle {
public:
    Vec3 position;
    Vec3 velocity;
    Vec3 force;
    double mass;

    Particle(const Vec3& position, double mass) : position(position), mass(mass), velocity(0, 0, 0), force(0, 0, 0) {}

    void applyForce(const Vec3& f) {
        force += f;
    }

    void integrate(double dt) {
        // Update velocity and position based on the current force and previous velocity.
        Vec3 acceleration = force * (1.0 / mass);
        velocity += acceleration * dt;
        position += velocity * dt;
        force = Vec3(0, 0, 0); // Reset force
    }
};

// Force Generators Interface
class ForceGenerator {
public:
    virtual void applyForce(Particle& particle) = 0;
};

// Gravity Force Generator
class GravityForceGenerator : public ForceGenerator {
    Vec3 gravity;

public:
    GravityForceGenerator(const Vec3& gravity) : gravity(gravity) {}

    void applyForce(Particle& particle) override {
        particle.applyForce(gravity * particle.mass);
    }
};

// World Class
class World {
    std::vector<std::unique_ptr<Particle>> particles;
    std::vector<std::unique_ptr<ForceGenerator>> forceGenerators;

public:
    void addParticle(std::unique_ptr<Particle> particle) {
        particles.push_back(std::move(particle));
    }

    void addForceGenerator(std::unique_ptr<ForceGenerator> forceGenerator) {
        forceGenerators.push_back(std::move(forceGenerator));
    }

    void update(double dt) {
        // Apply forces
        for (auto& fg : forceGenerators) {
            for (auto& p : particles) {
                fg->applyForce(*p);
            }
        }

        // Integrate physics
        for (auto& p : particles) {
            p->integrate(dt);
        }
    }

    void printParticles() const {
        for (const auto& p : particles) {
            std::cout << "Particle at (" << p->position.x << ", " << p->position.y << ", " << p->position.z << ")\n";
        }
    }
};

int main() {
    World world;

    // Add particles
    world.addParticle(std::make_unique<Particle>(Vec3(0, 10, 0), 1.0));
    world.addParticle(std::make_unique<Particle>(Vec3(0, 20, 0), 1.0));

    // Add gravity
    world.addForceGenerator(std::make_unique<GravityForceGenerator>(Vec3(0, -9.81, 0)));

    // Simulate for 3 seconds
    for (int i = 0; i < 300; ++i) {
        world.update(0.01);
        if (i % 60 == 0) { // Print every 60 iterations
            std::cout << "Time: " << i * 0.01 << "s\n";
            world.printParticles();
            std::cout << "\n";
        }
    }

    return 0;
}
