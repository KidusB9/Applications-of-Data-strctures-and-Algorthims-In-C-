#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    vector<int> point;
    Node* left;
    Node* right;
    int dim;

    Node(vector<int> p, int d) : point(p), left(nullptr), right(nullptr), dim(d) {}
};

Node* buildKDTree(vector<vector<int>>& points, int depth = 0) {
    if (points.empty()) return nullptr;

    int k = points[0].size();
    int axis = depth % k;

    sort(points.begin(), points.end(), [axis](const vector<int>& a, const vector<int>& b) {
        return a[axis] < b[axis];
    });

    int median = points.size() / 2;

    Node* node = new Node(points[median], axis);

    vector<vector<int>> left_points(points.begin(), points.begin() + median);
    vector<vector<int>> right_points(points.begin() + median + 1, points.end());

    node->left = buildKDTree(left_points, depth + 1);
    node->right = buildKDTree(right_points, depth + 1);

    return node;
}

double distance(const vector<int>& a, const vector<int>& b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

void nearestNeighborSearch(Node* root, const vector<int>& point, Node*& best, double& bestDist) {
    if (!root) return;

    double d = distance(root->point, point);
    double dx = root->point[root->dim] - point[root->dim];
    Node *near, *far;

    if (d < bestDist) {
        bestDist = d;
        best = root;
    }

    if (dx > 0) {
        near = root->left;
        far = root->right;
    } else {
        near = root->right;
        far = root->left;
    }

    nearestNeighborSearch(near, point, best, bestDist);

    if (abs(dx) < bestDist) {
        nearestNeighborSearch(far, point, best, bestDist);
    }
}

int main() {
    vector<vector<int>> points = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                                  {9, 1}, {2, 7}, {10, 19}};

    Node* root = buildKDTree(points);

    vector<int> target = {10, 15};

    Node* best = nullptr;
    double bestDist = numeric_limits<double>::max();

    nearestNeighborSearch(root, target, best, bestDist);

    if (best) {
        cout << "Nearest point is [";
        for (int i = 0; i < best->point.size(); ++i) {
            cout << best->point[i];
            if (i < best->point.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }

    return 0;
}
