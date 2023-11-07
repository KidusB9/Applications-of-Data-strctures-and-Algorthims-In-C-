#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class WebServer {
public:
    WebServer(int port, int poolSize) : port(port), poolSize(poolSize), server_fd(-1) {}

    ~WebServer() {
        if (server_fd != -1) {
            close(server_fd);
        }
    }

    bool start() {
        sockaddr_in address{};
        int opt = 1;

        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            std::cerr << "Socket failed" << std::endl;
            return false;
        }

        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            std::cerr << "Setsockopt failed" << std::endl;
            return false;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            return false;
        }

        if (listen(server_fd, 10) < 0) {
            std::cerr << "Listen failed" << std::endl;
            return false;
        }

        for (int i = 0; i < poolSize; ++i) {
            workers.emplace_back(&WebServer::handleConnections, this);
        }

        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }

        return true;
    }

private:
    void handleConnections() {
        while (true) {
            sockaddr_in address;
            socklen_t addrlen = sizeof(address);

            int socket = accept(server_fd, reinterpret_cast<sockaddr*>(&address), &addrlen);
            if (socket < 0) {
                std::cerr << "Accept failed" << std::endl;
                continue;
            }

            std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
            send(socket, response.c_str(), response.size(), 0);
            close(socket);
        }
    }

    int port;
    int poolSize;
    int server_fd;
    std::vector<std::thread> workers;
};

int main() {
    WebServer server(8080, 4); // Run on port 8080 with a thread pool of size 4
    if (!server.start()) {
        std::cerr << "Server failed to start" << std::endl;
        return 1;
    }
    return 0;
}
