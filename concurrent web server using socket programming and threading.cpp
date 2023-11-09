#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

std::atomic<bool> done(false);
std::mutex m;
std::condition_variable cv;

// Function to handle each client request
void handle_client(int client_socket) {
    const int buffer_size = 4096;
    char buffer[buffer_size];

    // Read the request from the client
    ssize_t bytes_received = recv(client_socket, buffer, buffer_size - 1, 0);
    if (bytes_received < 1) {
        std::cerr << "Connection closed by peer." << std::endl;
        close(client_socket);
        return;
    }

    // Just an example of response,   adjust if you want or add more data u see fit
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from the C++ Server!\n";
    
    // Send response
    send(client_socket, response.c_str(), response.size(), 0);

    // Close the socket
    close(client_socket);
}

// Function to start the server
void start_server(uint16_t port) {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Can't create a socket!" << std::endl;
        return;
    }

    // Bind the ip address and port to a socket
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Tell Winsock the socket is for listening
    listen(server_socket, SOMAXCONN);

    // Wait for connection
    while (!done) {
        sockaddr_in client;
        socklen_t client_size = sizeof(client);
        int client_socket = accept(server_socket, (sockaddr*)&client, &client_size);

        if (client_socket == -1) {
            std::cerr << "Problem with client connecting!" << std::endl;
            continue;
        }

        // Create a thread to handle the client
        std::thread client_thread(handle_client, client_socket);
        client_thread.detach(); // Detach the thread so it cleans up after finishing
    }

    close(server_socket);
}

int main() {
    std::cout << "Starting the server on port 8080" << std::endl;

    std::thread server_thread(start_server, 8080);

    // Wait for signal to shutdown
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return done; });

    server_thread.join();

    std::cout << "Server is shutting down" << std::endl;

    return 0;
}
