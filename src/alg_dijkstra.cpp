#include "algorithms.hpp"
#include <algorithm>
#include <vector>
#include <limits>

inline auto EdgeBetween(const Graph & graph, std::size_t a, std::size_t b)
{
    return std::find_if(
        graph.edges.begin(),
        graph.edges.end(),
        [&](const Edge & e) {
            return (e.a == a && e.b == b)
                || (e.a == b && e.b == a);
        }
    );
    
}

void DijkstraAlgorithm::run(const Graph & graph, GraphStateHistory & history)
{
    const int n = graph.nodes.size();
    std::vector<bool> visited(n, false);
    std::vector<int> distances(n,
        std::numeric_limits<int>::max());
    distances[0] = 0;

    for (int i = 0; i < n; i++) {
        // Find next node to explore.
        int current = -1;
        for (int j = 0; j < n; j++) {
            if (visited[j]) continue;
            if (current == -1 || distances[j] < distances[current])
                current = j;
        }

        // Find the node that the current node will connect to.
        int previous = -1;
        int bestDistance = std::numeric_limits<int>::max();
        for (auto & neighbor : graph.neighborsOf(current)) {
            if (!visited[neighbor.first]) continue;
            if (distances[neighbor.first] + neighbor.second < bestDistance) {
                bestDistance = distances[neighbor.first] + neighbor.second;
                previous = neighbor.first;
            }
        }

        // Set current node as visited and add node and edge to history.
        visited[current] = true;
        history.push([&](auto & s) {
            s.selectNode(current);
            auto e = EdgeBetween(graph, current, previous);
            if (e != graph.edges.end()) {
                s.selectEdge(std::distance(graph.edges.begin(), e));
            }
        });

        // Update the distances to the current node from its neighbors.
        for (int j = 0; j < n; j++) {
            auto e = EdgeBetween(graph, current, j);
            if (e != graph.edges.end()) {
                int path = distances[current] + e->weight;
                if (path < distances[j]) {
                    distances[j] = path;
                }
            }
        }
    }
}