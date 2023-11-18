#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>

class BankAccount {
protected:
    std::string accountNumber;
    double balance;

public:
    BankAccount(std::string accountNumber, double balance = 0.0)
        : accountNumber(std::move(accountNumber)), balance(balance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
    }

    const std::string& getAccountNumber() const {
        return accountNumber;
    }

    virtual void displayAccountInfo() const {
        std::cout << "Account Number: " << accountNumber << "\nBalance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
};

class Bank {
    std::unordered_map<std::string, std::unique_ptr<BankAccount>> accounts;

public:
    BankAccount* createAccount(const std::string& accountNumber, double initialDeposit) {
        auto account = std::make_unique<BankAccount>(accountNumber, initialDeposit);
        auto rawPtr = account.get();
        accounts[accountNumber] = std::move(account);
        return rawPtr;
    }

    BankAccount* getAccount(const std::string& accountNumber) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    void displayAllAccounts() const {
        for (const auto& pair : accounts) {
            pair.second->displayAccountInfo();
            std::cout << std::endl;
        }
    }
};

int main() {
    Bank bank;
    BankAccount* account1 = bank.createAccount("123456", 1000);
    BankAccount* account2 = bank.createAccount("987654", 500);

    account1->deposit(200);
    account2->withdraw(100);

    bank.displayAllAccounts();

    return 0;
}
