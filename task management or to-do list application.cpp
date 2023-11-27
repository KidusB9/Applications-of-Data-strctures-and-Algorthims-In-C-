#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Task {
    std::string description;
    bool completed;

public:
    Task(std::string desc) : description(std::move(desc)), completed(false) {}

    void complete() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    const std::string& getDescription() const {
        return description;
    }
};

class TaskManager {
    std::vector<std::unique_ptr<Task>> tasks;

public:
    void addTask(const std::string& description) {
        tasks.emplace_back(std::make_unique<Task>(description));
    }

    void completeTask(size_t taskIndex) {
        if (taskIndex < tasks.size()) {
            tasks[taskIndex]->complete();
        } else {
            std::cerr << "Invalid task index." << std::endl;
        }
    }

    void showTasks(bool showCompleted = false) const {
        for (size_t i = 0; i < tasks.size(); ++i) {
            const auto& task = tasks[i];
            if (showCompleted || !task->isCompleted()) {
                std::cout << i << ": " << task->getDescription()
                          << (task->isCompleted() ? " [Completed]" : "") << std::endl;
            }
        }
    }
};

int main() {
    TaskManager manager;
    manager.addTask("Learn C++");
    manager.addTask("Build a project");
    manager.addTask("Contribute to open source");

    manager.completeTask(0); // Mark the first task as complete

    std::cout << "All Tasks:" << std::endl;
    manager.showTasks(true); // Show all tasks

    std::cout << "\nPending Tasks:" << std::endl;
    manager.showTasks(); // Show only pending tasks

    return 0;
}
