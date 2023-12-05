#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Transaction {
    std::string type;
    double amount;

public:
    Transaction(std::string type, double amount) : type(std::move(type)), amount(amount) {}

    const std::string& getType() const {
        return type;
    }

    double getAmount() const {
        return amount;
    }
};

class Account {
    std::string accountNumber;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(std::string accountNumber, double initialDeposit)
        : accountNumber(std::move(accountNumber)), balance(initialDeposit) {
        transactions.emplace_back("Deposit", initialDeposit);
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        return true;
    }

    void printStatement() const {
        std::cout << "Account Statement for " << accountNumber << std::endl;
        for (const auto& transaction : transactions) {
            std::cout << transaction.getType() << ": " << transaction.getAmount() << std::endl;
        }
        std::cout << "Current Balance: " << balance << std::endl;
    }

    const std::string& getAccountNumber() const {
        return accountNumber;
    }
};

class Bank {
    std::unordered_map<std::string, std::unique_ptr<Account>> accounts;

public:
    Account* createAccount(const std::string& accountNumber, double initialDeposit) {
        auto account = std::make_unique<Account>(accountNumber, initialDeposit);
        auto rawPtr = account.get();
        accounts[accountNumber] = std::move(account);
        return rawPtr;
    }

    Account* getAccount(const std::string& accountNumber) {
        if (accounts.find(accountNumber) != accounts.end()) {
            return accounts[accountNumber].get();
        }
        return nullptr;
    }

    void depositToAccount(const std::string& accountNumber, double amount) {
        Account* account = getAccount(accountNumber);
        if (account) {
            account->deposit(amount);
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void withdrawFromAccount(const std::string& accountNumber, double amount) {
        Account* account = getAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void printAccountStatement(const std::string& accountNumber) {
        Account* account = getAccount(accountNumber);
        if (account) {
            account->printStatement();
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }
};

int main() {
    Bank bank;

    Account* acc1 = bank.createAccount("12345678", 1000.0);
    Account* acc2 = bank.createAccount("87654321", 500.0);

    bank.depositToAccount("12345678", 500.0);
    bank.withdrawFromAccount("87654321", 200.0);

    bank.printAccountStatement("12345678");
    bank.printAccountStatement("87654321");

    return 0;
}
