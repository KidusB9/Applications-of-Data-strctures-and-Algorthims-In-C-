#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BackEndManipulation {
private:
    vector<int> data;

public:
    // Add an element to the vector
    void addElement(int element) {
        data.push_back(element);
    }

    // Delete an element from the vector
    void deleteElement(int element) {
        auto it = find(data.begin(), data.end(), element);
        if (it != data.end()) {
            data.erase(it);
        }
    }

    // Display elements of the vector
    void displayElements() {
        for (const auto& element : data) {
            cout << element << ' ';
        }
        cout << endl;
    }

    // Sort the vector
    void sortData() {
        sort(data.begin(), data.end());
    }
};

int main() {
    BackEndManipulation backend;

    backend.addElement(5);
    backend.addElement(3);
    backend.addElement(7);
    backend.addElement(1);

    cout << "Before sorting: ";
    backend.displayElements();

    backend.sortData();

    cout << "After sorting: ";
    backend.displayElements();

    backend.deleteElement(3);

    cout << "After deleting 3: ";
    backend.displayElements();

    return 0;
}
