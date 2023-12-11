#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>

class Vehicle {
    std::string licensePlate;
public:
    Vehicle(std::string licensePlate) : licensePlate(std::move(licensePlate)) {}

    const std::string& getLicensePlate() const {
        return licensePlate;
    }
};

class ParkingSpace {
    int spaceNumber;
    bool occupied;
    time_t checkInTime;
    std::string vehicleLicense;

public:
    ParkingSpace(int number) : spaceNumber(number), occupied(false) {}

    bool isOccupied() const {
        return occupied;
    }

    void checkIn(const Vehicle& vehicle) {
        occupied = true;
        checkInTime = std::time(nullptr);
        vehicleLicense = vehicle.getLicensePlate();
    }

    double checkOut() {
        occupied = false;
        time_t now = std::time(nullptr);
        double hoursParked = std::difftime(now, checkInTime) / 3600.0;
        return hoursParked;
    }

    int getSpaceNumber() const {
        return spaceNumber;
    }

    const std::string& getVehicleLicense() const {
        return vehicleLicense;
    }
};

class ParkingLot {
    std::vector<ParkingSpace> spaces;
    double hourlyRate;

public:
    ParkingLot(int numSpaces, double rate) : spaces(numSpaces), hourlyRate(rate) {
        for (int i = 0; i < numSpaces; ++i) {
            spaces[i] = ParkingSpace(i + 1);
        }
    }

    bool parkVehicle(const Vehicle& vehicle) {
        for (auto& space : spaces) {
            if (!space.isOccupied()) {
                space.checkIn(vehicle);
                return true;
            }
        }
        return false;
    }

    double releaseVehicle(const std::string& licensePlate) {
        for (auto& space : spaces) {
            if (space.isOccupied() && space.getVehicleLicense() == licensePlate) {
                double hoursParked = space.checkOut();
                return hoursParked * hourlyRate;
            }
        }
        return -1.0; // Indicates vehicle not found
    }

    void printParkingSpaces() const {
        for (const auto& space : spaces) {
            std::cout << "Space " << space.getSpaceNumber() << ": "
                      << (space.isOccupied() ? space.getVehicleLicense() : "Empty") << std::endl;
        }
    }
};

int main() {
    ParkingLot lot(5, 2.0); // 5 spaces at $2/hour

    Vehicle car1("ABC123");
    Vehicle car2("XYZ789");
    
    lot.parkVehicle(car1);
    lot.parkVehicle(car2);

    std::cout << "Initial parking state:" << std::endl;
    lot.printParkingSpaces();

    // Simulate some time passing
    std::cout << "\nVehicle ABC123 parked for 2 hours, fee: $"
              << std::fixed << std::setprecision(2) << lot.releaseVehicle("ABC123") << std::endl;

    std::cout << "\nCurrent parking state:" << std::endl;
    lot.printParkingSpaces();

    return 0;
}
