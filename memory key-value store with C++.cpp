#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>

class KeyValueStore {
    std::unordered_map<std::string, std::string> store;

public:
    void set(const std::string& key, const std::string& value) {
        store[key] = value;
    }

    std::optional<std::string> get(const std::string& key) const {
        auto it = store.find(key);
        if (it != store.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

int main() {
    KeyValueStore store;
    
    store.set("key1", "value1");
    store.set("key2", "value2");

    auto value1 = store.get("key1");
    if (value1) {
        std::cout << "key1: " << *value1 << std::endl;
    } else {
        std::cout << "key1 not found." << std::endl;
    }

    auto value3 = store.get("key3");
    if (value3) {
        std::cout << "key3: " << *value3 << std::endl;
    } else {
        std::cout << "key3 not found." << std::endl;
    }

    return 0;
}
