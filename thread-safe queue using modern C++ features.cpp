#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue<T>&) = delete; // Disable copying
    ThreadSafeQueue& operator=(const ThreadSafeQueue<T>&) = delete; // Disable assignment

    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cv.notify_one(); // Notify one waiting thread
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return false;
        }
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); }); // Wait until the queue is not empty
        value = std::move(queue.front());
        queue.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }
};

void producer(ThreadSafeQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

void consumer(ThreadSafeQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        int value;
        queue.wait_and_pop(value);
        std::cout << "Consumer received: " << value << std::endl;
    }
}

int main() {
    ThreadSafeQueue<int> queue;

    std::thread producerThread(producer, std::ref(queue));
    std::thread consumerThread(consumer, std::ref(queue));

    producerThread.join();
    consumerThread.join();

    return 0;
}
