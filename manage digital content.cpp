#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

class Article {
    std::string title;
    std::string content;
    std::string author;

public:
    Article(std::string title, std::string content, std::string author)
        : title(std::move(title)), content(std::move(content)), author(std::move(author)) {}

    const std::string& getTitle() const {
        return title;
    }

    void updateContent(const std::string& newContent) {
        content = newContent;
    }

    void display() const {
        std::cout << "Article: " << title << "\nWritten by: " << author
                  << "\nContent: " << content << "\n\n";
    }
};

class User {
    std::string name;
    std::vector<std::shared_ptr<Article>> articles;

public:
    User(std::string name) : name(std::move(name)) {}

    void createArticle(const std::string& title, const std::string& content) {
        auto article = std::make_shared<Article>(title, content, name);
        articles.push_back(article);
    }

    std::shared_ptr<Article> getArticle(const std::string& title) {
        auto it = std::find_if(articles.begin(), articles.end(), [&title](const std::shared_ptr<Article>& article) {
            return article->getTitle() == title;
        });
        return it != articles.end() ? *it : nullptr;
    }

    void deleteArticle(const std::string& title) {
        articles.erase(std::remove_if(articles.begin(), articles.end(), [&title](const std::shared_ptr<Article>& article) {
            return article->getTitle() == title;
        }), articles.end());
    }

    void listArticles() const {
        for (const auto& article : articles) {
            std::cout << article->getTitle() << " by " << name << "\n";
        }
    }
};

class ContentManagementSystem {
    std::unordered_map<std::string, std::unique_ptr<User>> users;

public:
    void addUser(const std::string& userName) {
        users[userName] = std::make_unique<User>(userName);
    }

    User* getUser(const std::string& userName) {
        if (users.find(userName) != users.end()) {
            return users[userName].get();
        }
        return nullptr;
    }

    // Additional methods for managing content and searching will be added here
};

int main() {
    ContentManagementSystem cms;

    cms.addUser("Alice");
    cms.addUser("Bob");

    User* alice = cms.getUser("Alice");
    if (alice) {
        alice->createArticle("My First Article", "This is the content of my first article.");
        alice->createArticle("My Second Article", "This is the content of my second article.");
    }

    User* bob = cms.getUser("Bob");
    if (bob) {
        bob->createArticle("Bob's Insights", "Content of Bob's article.");
    }

    std::cout << "Articles by Alice:\n";
    alice->listArticles();

    std::cout << "\nArticles by Bob:\n";
    bob->listArticles();

    std::shared_ptr<Article> article = alice->getArticle("My First Article");
    if (article) {
        article->display();
    }

    return 0;
}
