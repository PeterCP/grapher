#include "algorithms.hpp"
#include <vector>

inline void SetBorderEdges(const Graph & graph, std::vector<bool> & visitedNodes,
                           std::vector<bool> & borderEdges)
{
    auto & edges = graph.edges;
    for (std::size_t i = 0; i < edges.size(); i++) {
        if ((visitedNodes[edges[i].a] && !visitedNodes[edges[i].b]) ||
                (visitedNodes[edges[i].b] && !visitedNodes[edges[i].a])) {
            borderEdges[i] = true;
        } else {
            borderEdges[i] = false;
        }
    }
}

inline bool IsFullyExplored(const std::vector<bool> & visitedNodes)
{
    for (const auto & v : visitedNodes) {
        if (!v) return false;
    }
    return true;
}

inline int GetBorderEdgeWithLowestWeight(const std::vector<Edge> & edges,
                                                 const std::vector<bool> & borderEdges)
{
    int res = -1;
    for (std::size_t i = 0; i < edges.size(); i++) {
        if (!borderEdges[i]) continue;
        if (res == -1 || edges[i].weight < edges[res].weight) {
            res = i;
        }
    }
    return res;
}

void PrimAlgorithm::run(const Graph & graph, GraphStateHistory & history)
{
    std::vector<bool> visitedNodes(graph.nodes.size(), false),
                      borderEdges(graph.edges.size(), false);

    // Set first node as visited and add it to history.
    visitedNodes[0] = true;
    history.push([](GraphState & s) {
        s.selectNode(0);
    });

    // Helper functions explain everything inside the loop.
    while (!IsFullyExplored(visitedNodes)) {
        SetBorderEdges(graph, visitedNodes, borderEdges);
        int i = GetBorderEdgeWithLowestWeight(graph.edges, borderEdges);
        auto & edge = graph.edges[i];
        visitedNodes[edge.a] = true;
        visitedNodes[edge.b] = true;
        history.push([&](GraphState & s) {
            s.selectNode(edge.a);
            s.selectNode(edge.b);
            s.selectEdge(i);
        });
    }
}
