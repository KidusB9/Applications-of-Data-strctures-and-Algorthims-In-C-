#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class Node;
class Edge;

using NodePtr = std::shared_ptr<Node>;
using EdgePtr = std::shared_ptr<Edge>;

class Node {
public:
    explicit Node(std::string id) : id_(std::move(id)) {}

    const std::string& GetId() const { return id_; }
    void AddEdge(const EdgePtr& edge) { edges_.push_back(edge); }
    const std::vector<EdgePtr>& GetEdges() const { return edges_; }

private:
    std::string id_;
    std::vector<EdgePtr> edges_;
};

class Edge {
public:
    Edge(NodePtr source, NodePtr target, std::string relation) 
        : source_(std::move(source)), target_(std::move(target)), relation_(std::move(relation)) {}

    const NodePtr& GetSource() const { return source_; }
    const NodePtr& GetTarget() const { return target_; }
    const std::string& GetRelation() const { return relation_; }

private:
    NodePtr source_;
    NodePtr target_;
    std::string relation_;
};

class Graph {
public:
    NodePtr CreateNode(const std::string& id) {
        auto node = std::make_shared<Node>(id);
        nodes_[id] = node;
        return node;
    }

    EdgePtr CreateEdge(const NodePtr& source, const NodePtr& target, const std::string& relation) {
        auto edge = std::make_shared<Edge>(source, target, relation);
        source->AddEdge(edge);
        return edge;
    }

    NodePtr GetNode(const std::string& id) const {
        auto it = nodes_.find(id);
        if (it != nodes_.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::vector<NodePtr> QueryNodesWithRelation(const std::string& relation) {
        std::vector<NodePtr> result;
        for (const auto& pair : nodes_) {
            auto& edges = pair.second->GetEdges();
            if (std::any_of(edges.begin(), edges.end(), [&relation](const EdgePtr& edge) {
                return edge->GetRelation() == relation;
            })) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

private:
    std::unordered_map<std::string, NodePtr> nodes_;
};

int main() {
    Graph graph;

    auto nodeA = graph.CreateNode("A");
    auto nodeB = graph.CreateNode("B");
    auto nodeC = graph.CreateNode("C");

    graph.CreateEdge(nodeA, nodeB, "knows");
    graph.CreateEdge(nodeB, nodeC, "likes");
    graph.CreateEdge(nodeC, nodeA, "hates");

    auto nodesWithKnowsRelation = graph.QueryNodesWithRelation("knows");
    std::cout << "Nodes with 'knows' relation:" << std::endl;
    for (const auto& node : nodesWithKnowsRelation) {
        std::cout << node->GetId() << std::endl;
    }

    return 0;
}
