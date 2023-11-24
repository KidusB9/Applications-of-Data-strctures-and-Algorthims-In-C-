#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

class VendingMachine {
    struct Item {
        std::string name;
        double price;
        int stock;

        Item(std::string name, double price, int stock)
            : name(std::move(name)), price(price), stock(stock) {}
    };

    std::unordered_map<int, Item> items;
    double currentBalance;

public:
    VendingMachine() : currentBalance(0.0) {}

    void addItem(int slot, const std::string& name, double price, int stock) {
        items[slot] = Item(name, price, stock);
    }

    void showItems() const {
        std::cout << "Items in Vending Machine:" << std::endl;
        for (const auto& item : items) {
            std::cout << "Slot " << item.first << ": " << item.second.name
                      << " - $" << std::fixed << std::setprecision(2) << item.second.price
                      << " (" << item.second.stock << " in stock)" << std::endl;
        }
    }

    void insertMoney(double amount) {
        currentBalance += amount;
        std::cout << "Current balance: $" << std::fixed << std::setprecision(2) << currentBalance << std::endl;
    }

    void selectItem(int slot) {
        if (items.find(slot) == items.end()) {
            std::cout << "Invalid slot selected." << std::endl;
            return;
        }

        Item& item = items[slot];
        if (item.stock <= 0) {
            std::cout << "Item out of stock." << std::endl;
            return;
        }

        if (currentBalance < item.price) {
            std::cout << "Insufficient balance." << std::endl;
            return;
        }

        item.stock--;
        currentBalance -= item.price;
        std::cout << "Dispensing " << item.name << ". Please take your item." << std::endl;
        giveChange();
    }

    void giveChange() {
        std::cout << "Returning change: $" << std::fixed << std::setprecision(2) << currentBalance << std::endl;
        currentBalance = 0.0;
    }
};

int main() {
    VendingMachine machine;
    machine.addItem(1, "Soda", 1.25, 10);
    machine.addItem(2, "Chips", 0.99, 15);
    machine.addItem(3, "Chocolate Bar", 1.50, 5);

    machine.showItems();
    machine.insertMoney(2.00);
    machine.selectItem(1);
    machine.selectItem(3);

    return 0;
}
