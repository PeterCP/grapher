#include "GraphState.hpp"

GraphState::GraphState(const std::size_t nodeCount, const std::size_t edgeCount)
    : exploredNodes(nodeCount, false)
    , exploredEdges(edgeCount, false)
{ }

GraphState::GraphState(const GraphState & other)
    : exploredNodes{ other.exploredNodes }
    , exploredEdges{ other.exploredEdges }
{ }

GraphState::GraphState(GraphState && other)
    : exploredNodes{ std::move(other.exploredNodes) }
    , exploredEdges{ std::move(other.exploredEdges) }
{ }

void GraphState::selectNode(std::size_t index)
{
    exploredNodes[index] = true;
}

void GraphState::selectEdge(std::size_t index)
{
    exploredEdges[index] = true;
}