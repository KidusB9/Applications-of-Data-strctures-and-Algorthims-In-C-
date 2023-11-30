#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

class Passenger {
    std::string name;
public:
    Passenger(std::string name) : name(std::move(name)) {}

    const std::string& getName() const {
        return name;
    }
};

class Flight {
    std::string flightNumber;
    std::string origin;
    std::string destination;
    int capacity;
    std::vector<Passenger> passengers;

public:
    Flight(std::string flightNumber, std::string origin, std::string destination, int capacity)
        : flightNumber(std::move(flightNumber)), origin(std::move(origin)), 
          destination(std::move(destination)), capacity(capacity) {}

    const std::string& getFlightNumber() const {
        return flightNumber;
    }

    bool addPassenger(const Passenger& passenger) {
        if (passengers.size() < capacity) {
            passengers.push_back(passenger);
            return true;
        }
        return false;
    }

    void listPassengers() const {
        for (const auto& passenger : passengers) {
            std::cout << passenger.getName() << std::endl;
        }
    }
};

class Booking {
    std::string bookingID;
    std::string flightNumber;
    std::string passengerName;

public:
    Booking(std::string bookingID, std::string flightNumber, std::string passengerName)
        : bookingID(std::move(bookingID)), flightNumber(std::move(flightNumber)), 
          passengerName(std::move(passengerName)) {}

    const std::string& getBookingID() const {
        return bookingID;
    }

    const std::string& getFlightNumber() const {
        return flightNumber;
    }

    const std::string& getPassengerName() const {
        return passengerName;
    }
};

class FlightBookingSystem {
    std::unordered_map<std::string, Flight> flights;
    std::unordered_map<std::string, Booking> bookings;

public:
    void createFlight(const std::string& flightNumber, const std::string& origin, 
                      const std::string& destination, int capacity) {
        flights[flightNumber] = Flight(flightNumber, origin, destination, capacity);
    }

    bool bookFlight(const std::string& bookingID, const std::string& flightNumber, 
                    const Passenger& passenger) {
        if (flights.find(flightNumber) != flights.end()) {
            if (flights[flightNumber].addPassenger(passenger)) {
                bookings[bookingID] = Booking(bookingID, flightNumber, passenger.getName());
                return true;
            }
        }
        return false;
    }

    void listBookings() const {
        for (const auto& pair : bookings) {
            const auto& booking = pair.second;
            std::cout << "Booking ID: " << booking.getBookingID()
                      << ", Flight: " << booking.getFlightNumber()
                      << ", Passenger: " << booking.getPassengerName() << std::endl;
        }
    }

    void listPassengersForFlight(const std::string& flightNumber) const {
        if (flights.find(flightNumber) != flights.end()) {
            std::cout << "Passengers for flight " << flightNumber << ":" << std::endl;
            flights.at(flightNumber).listPassengers();
        }
    }
};


int main() {
    FlightBookingSystem system;

    // Create some flights
    system.createFlight("FL123", "New York", "London", 5);
    system.createFlight("FL456", "Berlin", "Paris", 3);

    // Create passengers
    Passenger john("John Doe");
    Passenger jane("Jane Doe");
    Passenger bob("Bob Smith");

    // Book flights
    system.bookFlight("BK001", "FL123", john);
    system.bookFlight("BK002", "FL123", jane);
    system.bookFlight("BK003", "FL456", bob);

    // List all bookings
    std::cout << "All Bookings:" << std::endl;
    system.listBookings();

    // List passengers for a specific flight
    std::cout << "\nPassengers for FL123:" << std::endl;
    system.listPassengersForFlight("FL123");

    std::cout << "\nPassengers for FL456:" << std::endl;
    system.listPassengersForFlight("FL456");

    return 0;
}

