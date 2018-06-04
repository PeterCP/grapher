#include "algorithms.hpp"

GraphStateHistory Algorithm::operator()(Graph graph)
{
    GraphStateHistory history(graph);
    run(graph, history);
    return history;
}
