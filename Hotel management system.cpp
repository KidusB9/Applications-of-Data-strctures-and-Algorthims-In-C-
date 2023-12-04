#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Guest {
    std::string name;
public:
    Guest(std::string name) : name(std::move(name)) {}

    const std::string& getName() const {
        return name;
    }
};

class Room {
    int number;
    bool occupied;
    double rate;
public:
    Room(int number, double rate) : number(number), occupied(false), rate(rate) {}

    bool isOccupied() const {
        return occupied;
    }

    void setOccupied(bool occupiedStatus) {
        occupied = occupiedStatus;
    }

    int getNumber() const {
        return number;
    }

    double getRate() const {
        return rate;
    }
};

class Booking {
    int roomNumber;
    std::string guestName;
    int numberOfNights;
public:
    Booking(int room, std::string guest, int nights)
        : roomNumber(room), guestName(std::move(guest)), numberOfNights(nights) {}

    int getRoomNumber() const {
        return roomNumber;
    }

    const std::string& getGuestName() const {
        return guestName;
    }

    int getNumberOfNights() const {
        return numberOfNights;
    }
};

class Hotel {
    std::unordered_map<int, Room> rooms;
    std::vector<Booking> bookings;

public:
    void addRoom(int number, double rate) {
        rooms.emplace(number, Room(number, rate));
    }

    bool bookRoom(int roomNumber, const Guest& guest, int numberOfNights) {
        if (rooms.find(roomNumber) != rooms.end() && !rooms[roomNumber].isOccupied()) {
            rooms[roomNumber].setOccupied(true);
            bookings.emplace_back(roomNumber, guest.getName(), numberOfNights);
            return true;
        }
        return false;
    }

    void checkout(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            rooms[roomNumber].setOccupied(false);
        }
    }

    void listBookings() const {
        for (const auto& booking : bookings) {
            std::cout << "Room " << booking.getRoomNumber() 
                      << " booked by " << booking.getGuestName()
                      << " for " << booking.getNumberOfNights() << " nights." << std::endl;
        }
    }

    // Additional functionalities like billing, room services, etc., can be added here
};

int main() {
    Hotel myHotel;

    myHotel.addRoom(101, 100.0);
    myHotel.addRoom(102, 150.0);

    Guest guest1("John Doe");
    Guest guest2("Jane Smith");

    if (myHotel.bookRoom(101, guest1, 3)) {
        std::cout << "Room booked successfully." << std::endl;
    } else {
        std::cout << "Room booking failed." << std::endl;
    }

    if (myHotel.bookRoom(102, guest2, 2)) {
        std::cout << "Room booked successfully." << std::endl;
    } else {
        std::cout << "Room booking failed." << std::endl;
    }

    myHotel.listBookings();

    myHotel.checkout(101);

    return 0;
}
