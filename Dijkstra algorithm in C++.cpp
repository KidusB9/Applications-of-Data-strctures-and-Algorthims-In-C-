#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int INF = 1e9;

class Graph {
    private:
        int numVertices;
        std::vector<std::pair<int, int>>* edges;
    public:
        Graph(int numVertices);
        void addEdge(int v1, int v2, int weight);
        std::vector<int> shortestPath(int startVertex);
};

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    edges = new std::vector<std::pair<int, int>>[numVertices];
}

void Graph::addEdge(int v1, int v2, int weight) {
    edges[v1].push_back({v2, weight});
    edges[v2].push_back({v1, weight});
}

std::vector<int> Graph::shortestPath(int startVertex) {
    std::vector<int> distance(numVertices, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

    distance[startVertex] = 0;
    q.push({0, startVertex});

    while (!q.empty()) {
        int v = q.top().second;
        q.pop();

        for (std::pair<int, int> edge : edges[v]) {
            int to = edge.first;
            int weight = edge.second;

            if (distance[to] > distance[v] + weight) {
                distance[to] = distance[v] + weight;
                q.push({distance[to], to});
            }
        }
    }

    return distance;
}
