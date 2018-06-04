#include "GraphStateHistory.hpp"

GraphStateHistory::GraphStateHistory(Graph & graph)
    : graph{ graph }
{
    states.push_back(GraphState(graph.nodes.size(), graph.edges.size()));
}

void GraphStateHistory::push(std::function<void(GraphState &)> transform)
{
    GraphState newState = states.back();
    transform(newState);
    states.push_back(newState);
}
