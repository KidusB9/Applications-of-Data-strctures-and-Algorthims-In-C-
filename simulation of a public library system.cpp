#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Book {
    std::string title;
    std::string author;
    bool checkedOut;

public:
    Book(std::string title, std::string author)
        : title(std::move(title)), author(std::move(author)), checkedOut(false) {}

    void checkout() {
        checkedOut = true;
    }

    void returnBook() {
        checkedOut = false;
    }

    bool isAvailable() const {
        return !checkedOut;
    }

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getAuthor() const {
        return author;
    }
};

class Library {
    std::vector<Book> books;
    std::unordered_map<std::string, int> memberAccounts;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void registerMember(const std::string& name) {
        memberAccounts[name] = 0;
    }

    bool checkoutBook(const std::string& title, const std::string& memberName) {
        for (auto& book : books) {
            if (book.getTitle() == title && book.isAvailable()) {
                book.checkout();
                memberAccounts[memberName]++;
                return true;
            }
        }
        return false;
    }

    void returnBook(const std::string& title, const std::string& memberName) {
        for (auto& book : books) {
            if (book.getTitle() == title && !book.isAvailable()) {
                book.returnBook();
                memberAccounts[memberName]--;
                return;
            }
        }
    }

    void listAvailableBooks() const {
        for (const auto& book : books) {
            if (book.isAvailable()) {
                std::cout << book.getTitle() << " by " << book.getAuthor() << std::endl;
            }
        }
    }
};

int main() {
    Library library;
    library.addBook(Book("1984", "George Orwell"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

    library.registerMember("John Doe");

    library.checkoutBook("1984", "Kidus Berhanu");
    std::cout << "Books available after checkout:" << std::endl;
    library.listAvailableBooks();

    library.returnBook("1984", "Homer simpson");
    std::cout << "\nBooks available after return:" << std::endl;
    library.listAvailableBooks();

    return 0;
}
