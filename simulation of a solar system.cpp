#include <iostream>
#include <vector>
#include <cmath>

const double G = 6.67430e-11; // Gravitational constant

struct Vector3 {
    double x, y, z;

    Vector3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalized() const {
        double mag = magnitude();
        return Vector3(x / mag, y / mag, z / mag);
    }
};

class CelestialBody {
public:
    Vector3 position;
    Vector3 velocity;
    double mass;

    CelestialBody(double mass, Vector3 position, Vector3 velocity) : mass(mass), position(position), velocity(velocity) {}

    void applyGravity(const CelestialBody& other, double timestep) {
        Vector3 direction = other.position - position;
        double distance = direction.magnitude();
        double forceMagnitude = G * mass * other.mass / (distance * distance);
        Vector3 force = direction.normalized() * forceMagnitude;
        Vector3 acceleration = force / mass;
        velocity = velocity + acceleration * timestep;
    }

    void update(double timestep) {
        position = position + velocity * timestep;
    }
};

class SolarSystem {
    std::vector<CelestialBody> bodies;

public:
    void addBody(const CelestialBody& body) {
        bodies.push_back(body);
    }

    void update(double timestep) {
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = 0; j < bodies.size(); ++j) {
                if (i != j) {
                    bodies[i].applyGravity(bodies[j], timestep);
                }
            }
        }

        for (auto& body : bodies) {
            body.update(timestep);
        }
    }

    void printPositions() const {
        for (const auto& body : bodies) {
            std::cout << "Body at (" << body.position.x << ", " << body.position.y << ", " << body.position.z << ")" << std::endl;
        }
    }
};

int main() {
    SolarSystem solarSystem;

    // Adding the sun and some planets
    solarSystem.addBody(CelestialBody(1.989e30, Vector3(0, 0, 0), Vector3(0, 0, 0))); // Sun
    solarSystem.addBody(CelestialBody(5.972e24, Vector3(147.09e9, 0, 0), Vector3(0, 30290, 0))); // Earth
    solarSystem.addBody(CelestialBody(6.39e23, Vector3(206.62e9, 0, 0), Vector3(0, 26500, 0))); // Mars

    // Simulating the solar system for one day
    for (int i = 0; i < 24; ++i) {
        solarSystem.update(3600); // Update every hour
        std::cout << "Hour " << i + 1 << std::endl;
        solarSystem.printPositions();
    }

    return 0;
}
