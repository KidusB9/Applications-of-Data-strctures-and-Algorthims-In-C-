#include <iostream>
#include <utility>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePtr() {
        delete ptr;
    }

    // Move constructor
    UniquePtr(UniquePtr&& moving) noexcept : ptr(moving.ptr) {
        moving.ptr = nullptr;
    }

    // Move assignment operator
    UniquePtr& operator=(UniquePtr&& moving) noexcept {
        if (this != &moving) {
            delete ptr; // Free the old resource
            ptr = moving.ptr;
            moving.ptr = nullptr;
        }
        return *this;
    }

    // Deleted copy constructor and assignment operator to prevent copying
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Overload * and -> operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Utility functions
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    T* get() const { return ptr; }

    explicit operator bool() const { return ptr != nullptr; }
};

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void doSomething() { std::cout << "Doing something\n"; }
};

int main() {
    {
        UniquePtr<Resource> resPtr(new Resource());
        resPtr->doSomething();
    } // resPtr goes out of scope and the Resource is destroyed automatically

    return 0;
}
