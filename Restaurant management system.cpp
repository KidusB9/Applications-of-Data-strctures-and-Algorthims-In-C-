#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Dish {
    std::string name;
    double price;

public:
    Dish(std::string name, double price) : name(std::move(name)), price(price) {}

    const std::string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

class Menu {
    std::unordered_map<std::string, Dish> dishes;

public:
    void addDish(const Dish& dish) {
        dishes[dish.getName()] = dish;
    }

    const Dish* getDish(const std::string& name) const {
        auto it = dishes.find(name);
        if (it != dishes.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void printMenu() const {
        std::cout << "Menu:" << std::endl;
        for (const auto& pair : dishes) {
            std::cout << pair.first << " - $" << pair.second.getPrice() << std::endl;
        }
    }
};

class Table {
    int number;
    bool occupied;

public:
    Table(int number) : number(number), occupied(false) {}

    void occupy() {
        occupied = true;
    }

    void release() {
        occupied = false;
    }

    bool isOccupied() const {
        return occupied;
    }

    int getNumber() const {
        return number;
    }
};

class Order {
    int tableNumber;
    std::vector<Dish> dishes;

public:
    Order(int tableNumber) : tableNumber(tableNumber) {}

    void addDish(const Dish& dish) {
        dishes.push_back(dish);
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& dish : dishes) {
            total += dish.getPrice();
        }
        return total;
    }

    void printOrder() const {
        std::cout << "Order for table " << tableNumber << std::endl;
        for (const auto& dish : dishes) {
            std::cout << dish.getName() << " - $" << dish.getPrice() << std::endl;
        }
        std::cout << "Total: $" << calculateTotal() << std::endl;
    }
};

class Restaurant {
    Menu menu;
    std::vector<Table> tables;
    std::vector<Order> orders;

public:
    Restaurant(int numTables) : tables(numTables) {
        for (int i = 0; i < numTables; ++i) {
            tables[i] = Table(i + 1);
        }
    }

    void addDishToMenu(const Dish& dish) {
        menu.addDish(dish);
    }

    bool occupyTable(int tableNumber) {
        if (tableNumber > 0 && tableNumber <= tables.size() && !tables[tableNumber - 1].isOccupied()) {
            tables[tableNumber - 1].occupy();
            return true;
        }
        return false;
    }

    void releaseTable(int tableNumber) {
        if (tableNumber > 0 && tableNumber <= tables.size()) {
            tables[tableNumber - 1].release();
        }
    }

    void createOrder(int tableNumber) {
        if (tableNumber > 0 && tableNumber <= tables.size()) {
            orders.emplace_back(tableNumber);
        }
    }

    void addDishToOrder(int tableNumber, const std::string& dishName) {
        const Dish* dish = menu.getDish(dishName);
        if (dish && tableNumber > 0 && tableNumber <= orders.size()) {
            orders[tableNumber - 1].addDish(*dish);
        }
    }

    void printOrders() const {
        for (const auto& order : orders) {
            order.printOrder();
            std::cout << std::endl;
        }
    }

    void printMenu() const {
        menu.printMenu();
    }
};

int main() {
    Restaurant restaurant(5);
    restaurant.addDishToMenu(Dish("Pizza", 10.99));
    restaurant.addDishToMenu(Dish("Pasta", 8.99));
    restaurant.addDishToMenu(Dish("Burger", 6.99));

    restaurant.occupyTable(1);
    restaurant.createOrder(1);
    restaurant.addDishToOrder(1, "Pizza");
    restaurant.addDishToOrder(1, "Pasta");

    restaurant.occupyTable(2);
    restaurant.createOrder(2);
    restaurant.addDishToOrder(2, "Burger");

    std::cout << "Current Orders:" << std::endl;
    restaurant.printOrders();

    restaurant.releaseTable(1);
    restaurant.releaseTable(2);

    return 0;
}
