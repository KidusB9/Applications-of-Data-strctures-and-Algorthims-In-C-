#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <optional>

class Record {
    std::unordered_map<std::string, std::string> fields;
public:
    void setField(const std::string& fieldName, const std::string& value) {
        fields[fieldName] = value;
    }

    std::optional<std::string> getField(const std::string& fieldName) const {
        auto it = fields.find(fieldName);
        if (it != fields.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    bool matchesQuery(const std::string& fieldName, const std::string& value) const {
        auto it = fields.find(fieldName);
        return it != fields.end() && it->second == value;
    }
};

class Table {
    std::vector<Record> records;
    std::vector<std::string> fieldNames;

public:
    Table(const std::vector<std::string>& fields) : fieldNames(fields) {}

    void insertRecord(const Record& record) {
        records.push_back(record);
    }

    std::vector<Record> queryRecords(const std::string& fieldName, const std::string& value) const {
        std::vector<Record> result;
        for (const auto& record : records) {
            if (record.matchesQuery(fieldName, value)) {
                result.push_back(record);
            }
        }
        return result;
    }

    void displayAllRecords() const {
        for (const auto& record : records) {
            for (const auto& fieldName : fieldNames) {
                if (auto value = record.getField(fieldName); value) {
                    std::cout << fieldName << ": " << *value << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

class Database {
    std::unordered_map<std::string, Table> tables;

public:
    void createTable(const std::string& tableName, const std::vector<std::string>& fields) {
        tables[tableName] = Table(fields);
    }

    Table* getTable(const std::string& tableName) {
        auto it = tables.find(tableName);
        if (it != tables.end()) {
            return &it->second;
        }
        return nullptr;
    }
};

int main() {
    Database db;
    db.createTable("Employees", {"Name", "Position", "Department"});

    Table* employees = db.getTable("Employees");
    if (employees) {
        Record rec1;
        rec1.setField("Name", "John Doe");
        rec1.setField("Position", "Manager");
        rec1.setField("Department", "Sales");
        
        Record rec2;
        rec2.setField("Name", "Jane Smith");
        rec2.setField("Position", "Developer");
        rec2.setField("Department", "IT");

        employees->insertRecord(rec1);
        employees->insertRecord(rec2);

        std::cout << "All Employees:" << std::endl;
        employees->displayAllRecords();
    }

    return 0;
}
