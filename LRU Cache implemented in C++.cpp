#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache; // Doubly-linked list to store <key, value>
    unordered_map<int, list<pair<int, int>>::iterator> map; // Map to look up nodes in the list

public:
    LRUCache(int c) : capacity(c) {}

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;
        }

        // Move the accessed node to the front of the list
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            // Update the value and move the node to the front of the list
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        // Insert the new key-value pair
        if (cache.size() == capacity) {
            int keyToRemove = cache.back().first;
            cache.pop_back();
            map.erase(keyToRemove);
        }
        cache.emplace_front(key, value);
        map[key] = cache.begin();
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "Get key 1: " << cache.get(1) << endl; // should return 1

    cache.put(3, 3); // evicts key 2
    cout << "Get key 2: " << cache.get(2) << endl; // should return -1 (not found)

    cache.put(4, 4); // evicts key 1
    cout << "Get key 1: " << cache.get(1) << endl; // should return -1 (not found)
    cout << "Get key 3: " << cache.get(3) << endl; // should return 3
    cout << "Get key 4: " << cache.get(4) << endl; // should return 4

    return 0;
}
