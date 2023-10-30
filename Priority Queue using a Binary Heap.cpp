#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class MinHeap {
private:
    vector<int> heap;

    // Helper functions for heap manipulation
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        if (left(i) < heap.size() && heap[left(i)] < heap[i])
            smallest = left(i);
        if (right(i) < heap.size() && heap[right(i)] < heap[smallest])
            smallest = right(i);

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Insert a new element
    void push(int key) {
        heap.push_back(key);
        int index = heap.size() - 1;
        heapifyUp(index);
    }

    // Remove and return the smallest element
    int pop() {
        if (heap.empty()) throw invalid_argument("Heap is empty!");

        int root = heap.front();

        heap[0] = heap.back();
        heap.pop_back();

        heapifyDown(0);

        return root;
    }

    // Peek at the smallest element without removing it
    int top() {
        if (heap.empty()) throw invalid_argument("Heap is empty!");

        return heap.front();
    }

    // Check if heap is empty
    bool empty() {
        return heap.size() == 0;
    }

    // Return the size of the heap
    int size() {
        return heap.size();
    }
};

int main() {
    MinHeap minHeap;

    minHeap.push(3);
    minHeap.push(2);
    minHeap.push(15);
    minHeap.push(5);
    minHeap.push(4);
    minHeap.push(45);

    cout << "Size of the heap: " << minHeap.size() << endl;

    cout << minHeap.pop() << " ";
    cout << minHeap.top() << " ";

    return 0;
}
