#pragma once

#include <vector>
#include <functional>
#include "GraphState.hpp"

class GraphStateHistory
{
public:
    std::vector<GraphState> states;
    Graph graph;

    GraphStateHistory(Graph & graph);

    void push(std::function<void(GraphState &)> transform);
};
