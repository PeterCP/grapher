#include "algorithms.hpp"
#include <vector>

class DisjointSet
{
public:
    std::vector<int> rank, parents;

    DisjointSet(int n)
        : rank(n, 0)
        , parents(n)
    {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }

    int find(int index)
    {
        if (index != parents[index])
            parents[index] = find(parents[index]);
        return parents[index];
    }

    void merge(int a, int b)
    {
        a = find(a),
        b = find(b);

        if (rank[a] > rank[b])
            parents[b] = a;
        else
            parents[a] = b;

        if (rank[a] == rank[b])
            rank[b]++;
    }
};

void KruskalAlgorithm::run(const Graph & graph, GraphStateHistory & history)
{
    auto & edges = graph.edges;
    std::vector<bool> exploredEdges(edges.size(), false);
    DisjointSet ds(graph.nodes.size());

    for (std::size_t _ = 0; _ < edges.size(); _++) {
        // Find next unexplored edge with the lowest weight.
        int index = -1;
        for (std::size_t i = 0; i < edges.size(); i++) {
            if (!exploredEdges[i] && (index == -1 || edges[i].weight < edges[index].weight)) {
                index = i;
            }
        }

        // Set edge as explored
        exploredEdges[index] = true;
        
        // Find parents for the nodes connected by the edge.
        int a = ds.find(edges[index].a),
            b = ds.find(edges[index].b);
        
        // If the nodes aren't connected, connect them and add that to the history.
        if (a != b) {
            ds.merge(a, b);

            history.push([&](GraphState & s) {
                s.selectEdge(index);
                s.selectNode(edges[index].a);
                s.selectNode(edges[index].b);
            });
        }
    }
}
