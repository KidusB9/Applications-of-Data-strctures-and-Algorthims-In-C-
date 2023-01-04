#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

// A struct to represent a ticket
struct Ticket {
  string name;
  int price;
};

// A struct to represent a cinema
struct Cinema {
  string name;
  queue<Ticket> tickets;
};

// A hash map to store the cinemas
unordered_map<string, Cinema> cinemas;

// A function to add a cinema to the hash map
void addCinema(string name) {
  Cinema cinema;
  cinema.name = name;
  cinemas[name] = cinema;
}

// A function to add a ticket to a cinema's queue
void addTicket(string cinemaName, Ticket ticket) {
  cinemas[cinemaName].tickets.push(ticket);
}

// A function to sell a ticket from a cinema's queue
void sellTicket(string cinemaName) {
  if (cinemas[cinemaName].tickets.empty()) {
    cout << "Sorry, there are no more tickets available for " << cinemaName << endl;
  } else {
    Ticket ticket = cinemas[cinemaName].tickets.front();
    cinemas[cinemaName].tickets.pop();
    cout << "Sold 1 ticket for " << ticket.name << " for $" << ticket.price << endl;
  }
}

int main() {
  // Add some cinemas
  addCinema("Cinema 1");
  addCinema("Cinema 2");
  addCinema("Cinema 3");

  // Add some tickets to Cinema 1
  addTicket("Cinema 1", {"Movie A", 10});
  addTicket("Cinema 1", {"Movie B", 15});
  addTicket("Cinema 1", {"Movie C", 12});

  // Sell a ticket from Cinema 1
  sellTicket("Cinema 1"); // Sold 1 ticket for Movie A for $10
  sellTicket("Cinema 1"); // Sold 1 ticket for Movie B for $15

  // Add some tickets to Cinema 2
  addTicket("Cinema 2", {"Movie D", 8});
  addTicket("Cinema 2", {"Movie E", 9});

  // Sell a ticket from Cinema 2
  sellTicket("Cinema 2"); // Sold 1 ticket for Movie D for $8

  // Try to sell a ticket from an empty queue
  sellTicket("Cinema 3"); // Sorry, there are no more tickets available for Cinema 3

  return 0;
}
