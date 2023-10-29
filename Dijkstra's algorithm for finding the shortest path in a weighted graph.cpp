#include <iostream>
#include <vector>
#include <queue>
#include <utility> // for std::pair
#include <limits>  // for std::numeric_limits

using namespace std;

// Edge class to represent a directed edge with weight
struct Edge {
    int dest, weight;
    Edge(int dest, int weight) : dest(dest), weight(weight) {}
};

// Dijkstra's algorithm implementation
vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : graph[u]) {
            int v = edge.dest, weight = edge.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    // Representing the graph as an adjacency list
    // The graph is: 0--(1)--1--(4)--2
    //                \       / \      / 
    //                (7)   (2) (3)  (5)
    //                  \   /     \  /  
    //                   3--------4
    vector<vector<Edge>> graph = {
        {{1, 1}, {3, 7}},                // Node 0
        {{0, 1}, {2, 4}, {3, 2}, {4, 3}}, // Node 1
        {{1, 4}, {4, 5}},                // Node 2
        {{0, 7}, {1, 2}, {4, 6}},        // Node 3
        {{1, 3}, {2, 5}, {3, 6}}         // Node 4
    };

    int start = 0;
    vector<int> dist = dijkstra(graph, start);

    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        cout << "To " << i << ": " << dist[i] << endl;
    }

    return 0;
}
