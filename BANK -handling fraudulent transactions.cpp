#this is an example which i took from my recent projects, can be adjusted and  for the specfic banks and cam be tailrod to their needs.
#include <iostream>
#include <unordered_map>
#include <queue>

class BankAccount {
public:
    BankAccount(int accountNumber, double initialBalance = 0)
        : accountNumber(accountNumber), balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

private:
    int accountNumber;
    double balance;
};

class Bank {
public:
    void createAccount(int accountNumber, double initialBalance) {
        accounts[accountNumber] = BankAccount(accountNumber, initialBalance);
    }

    bool deposit(int accountNumber, double amount) {
        if (accounts.find(accountNumber) == accounts.end()) {
            return false;
        }
        accounts[accountNumber].deposit(amount);

        // Check for potential fraud
        return checkFraud(accountNumber, amount);
    }

    bool checkFraud(int accountNumber, double amount) {
        auto &q = transactionHistory[accountNumber];

        // Add current transaction to the queue
        q.push(amount);

        // If we have more than N transactions, remove the oldest
        if (q.size() > N) {
            q.pop();
        }

        // Sum up the last N transactions
        double sum = 0;
        for (auto &x : q) {
            sum += x;
        }

        // Flag potential fraud
        if (sum > threshold) {
            std::cout << "Potential fraud detected for account " << accountNumber << std::endl;
            return true;
        }

        return false;
    }

private:
    std::unordered_map<int, BankAccount> accounts;
    std::unordered_map<int, std::queue<double>> transactionHistory;
    const int N = 3; // Number of transactions to consider for fraud detection
    const double threshold = 10000; // Threshold for fraud detection
};

int main() {
    Bank myBank;
    myBank.createAccount(1001, 500.0);
    myBank.createAccount(1002, 300.0);

    // Normal transactions
    myBank.deposit(1001, 200);
    myBank.deposit(1002, 300);

    // Potentially fraudulent transactions
    myBank.deposit(1001, 4000);
    myBank.deposit(1001, 6000);
    myBank.deposit(1001, 7000);  // This should trigger the fraud detection

    return 0;
}
