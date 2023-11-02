#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>

// Networking libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

constexpr int MAX_CLIENTS = 10;
constexpr int BUFFER_SIZE = 4096;
constexpr int PORT = 8080;

std::mutex connection_queue_mutex;
std::condition_variable connection_condition;
std::queue<int> connection_queue;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    // Read the request
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 1) {
        std::cout << "Connection closed by peer." << std::endl;
        close(client_socket);
        return;
    }

    std::cout << "Received message from client: " << std::string(buffer) << std::endl;

    // Send a basic HTTP response
    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from the C++ Web Server!";
    send(client_socket, response.str().c_str(), response.str().size(), 0);

    close(client_socket);
}

void connection_handler() {
    while (true) {
        std::unique_lock<std::mutex> lock(connection_queue_mutex);
        connection_condition.wait(lock, [] { return !connection_queue.empty(); });

        int client_socket = connection_queue.front();
        connection_queue.pop();
        lock.unlock();

        handle_client(client_socket);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Start the connection handling thread
    std::vector<std::thread> threads;
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        threads.emplace_back(std::thread(connection_handler));
    }

    // Accept incoming connections
    std::cout << "Listening on port " << PORT << "..." << std::endl;
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        {
            std::lock_guard<std::mutex> guard(connection_queue_mutex);
            connection_queue.push(new_socket);
        }
        connection_condition.notify_one();
    }

    // Cleanup
    for (auto& t : threads) {
        t.join();
    }
    close(server_fd);

    return 0;
}
