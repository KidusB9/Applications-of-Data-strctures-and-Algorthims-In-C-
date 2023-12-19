#include <iostream>
#include <string>
#include <cstdlib>
#include <array>

class NetworkDiagnostics {
public:
    void pingHost(const std::string& hostname) {
        std::string command = "ping -c 4 " + hostname;
        executeCommand(command.c_str());
    }

    void tracerouteHost(const std::string& hostname) {
        std::string command = "traceroute " + hostname;
        executeCommand(command.c_str());
    }

    void showIPConfig() {
        std::string command = "ifconfig";
        executeCommand(command.c_str());
    }

private:
    void executeCommand(const char* cmd) {
        std::array<char, 128> buffer;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            std::cerr << "Failed to run command" << std::endl;
            return;
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            std::cout << buffer.data();
        }
    }
};

void showUsage() {
    std::cout << "Network Diagnostics Tool\n"
              << "Usage:\n"
              << "  ping <hostname>\n"
              << "  traceroute <hostname>\n"
              << "  ipconfig\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showUsage();
        return 1;
    }

    NetworkDiagnostics nd;
    std::string command = argv[1];

    if (command == "ping" && argc == 3) {
        nd.pingHost(argv[2]);
    } else if (command == "traceroute" && argc == 3) {
        nd.tracerouteHost(argv[2]);
    } else if (command == "ipconfig") {
        nd.showIPConfig();
    } else {
        showUsage();
    }

    return 0;
}
