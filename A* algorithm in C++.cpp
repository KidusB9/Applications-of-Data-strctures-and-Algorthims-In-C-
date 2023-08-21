#kidus berhanu#
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

const int INF = 1e9;


struct Node {
    int x, y;
    int f, g, h;
};

class AStar {
    private:
        std::vector<std::vector<int>> grid;
        std::unordered_map<int, std::unordered_map<int, bool isClosed;
        public:
    AStar(std::vector<std::vector<int>> grid);
    std::vector<Node> findPath(Node start, Node end);
};

AStar::AStar(std::vector<std::vector<int>> grid) {
this->grid = grid;
}

std::vector<Node> AStar::findPath(Node start, Node end) {
std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;
std::unordered_map<int, std::unordered_map<int, Node>> cameFrom;
isClosed = std::unordered_map<int, std::unordered_map<int, bool>>();
auto getCost = [&](int x, int y) {
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) {
        return INF;
    }
    return grid[x][y];
};

auto heuristic = [&](Node a, Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
};

start.g = 0;
start.h = heuristic(start, end);
start.f = start.g + start.h;
open.push(start);

while (!open.empty()) {
    Node current = open.top();
    open.pop();

    if (current.x == end.x && current.y == end.y) {
        std::vector<Node> path;
        path.push_back(current);
        while (cameFrom.count(current.x) && cameFrom[current.x].count(current.y)) {
            current = cameFrom[current.x][current.y];
            path.push_back(current);
        }
        return path;
    }

    isClosed[current.x][current.y] = true;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int x = current.x + dx, y = current.y + dy;
            if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || (dx == 0 && dy == 0) || isClosed[x][y]) {
                continue;
            }

            int gScore = current.g + getCost(x, y);
            if (!cameFrom.count(x) || !cameFrom[x].count(y) || gScore < cameFrom[x][y].g) {
                Node neighbor;
                neighbor.x = x;
                neighbor.y = y;
                neighbor.g = gScore;
                neighbor.h = heuristic(neighbor, end);
                neighbor.f = neighbor.g + neighbor.h;
                cameFrom[x][y] = current;
                open.push(neighbor);
            }
        }
    }
}
return {};

