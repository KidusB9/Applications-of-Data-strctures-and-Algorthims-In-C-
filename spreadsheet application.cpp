#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>

// Forward declarations
class Cell;
class Row;
class Spreadsheet;

enum class CellType { Empty, Numeric, Formula };

class Cell {
    friend class Row;
    friend class Spreadsheet;

    std::string content;
    double numericValue;
    CellType type;
    std::function<double()> formula;
    Row* parentRow;

    double evaluate() {
        if (type == CellType::Numeric) {
            return numericValue;
        } else if (type == CellType::Formula) {
            return formula();
        }
        return 0.0;
    }

public:
    Cell() : content(""), numericValue(0.0), type(CellType::Empty), parentRow(nullptr) {}

    void setContent(const std::string& content) {
        this->content = content;
        parseContent();
    }

    const std::string& getContent() const {
        return content;
    }

    double getValue() const {
        return evaluate();
    }

private:
    void parseContent() {
        if (content.empty()) {
            type = CellType::Empty;
        } else if (isdigit(content[0])) {
            type = CellType::Numeric;
            numericValue = std::stod(content);
        } else if (content[0] == '=') {
            type = CellType::Formula;
            // Formula parsing logic goes here
            // For now, let's just store a dummy formula that returns 0
            formula = [] { return 0.0; };
        }
    }
};

class Row {
    friend class Spreadsheet;

    std::vector<Cell> cells;
    int rowIndex;
    Spreadsheet* parentSpreadsheet;

public:
    Row(int size, int rowIndex, Spreadsheet* parent) : cells(size), rowIndex(rowIndex), parentSpreadsheet(parent) {
        for (auto& cell : cells) {
            cell.parentRow = this;
        }
    }

    Cell& operator[](int index) {
        return cells.at(index);
    }
};

class Spreadsheet {
    std::vector<Row> rows;
    int width, height;

public:
    Spreadsheet(int width, int height) : width(width), height(height), rows(height, Row(width, 0, this)) {
        int rowIndex = 0;
        for (auto& row : rows) {
            row.rowIndex = rowIndex++;
        }
    }

    Row& operator[](int index) {
        return rows.at(index);
    }

    void display() const {
        for (const auto& row : rows) {
            for (const auto& cell : row.cells) {
                std::cout << cell.getValue() << "\t";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Spreadsheet sheet(3, 3);
    sheet[0][0].setContent("123");
    sheet[1][1].setContent("456");
    sheet[2][2].setContent("=A1+B2");

    sheet.display();

    return 0;
}
