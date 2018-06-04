#pragma once

#include <vector>
#include "Graph.hpp"

class GraphState
{
public:
    GraphState(const std::size_t nodeCount, const std::size_t edgeCount);

    GraphState(const GraphState & other);

    GraphState(GraphState && other);

    void selectNode(std::size_t nodeIndex);

    void selectEdge(std::size_t edgeIndex);

    std::vector<bool> exploredNodes, exploredEdges;
};
