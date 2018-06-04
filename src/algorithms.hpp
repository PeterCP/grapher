#pragma once

#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphStateHistory.hpp"

class Algorithm
{
public:
    /**
     * Called externally to run the algorithm. The graph is passed by value
     * to avoid mutating the original graph.
     */
    GraphStateHistory operator()(Graph graph);

protected:
    /**
     * Run the algorithm. This method has to be implemented by each concrete
     * subclass.
     */
    virtual void run(const Graph & graph, GraphStateHistory & states) = 0;
};

class DijkstraAlgorithm : public Algorithm
{
protected:
    virtual void run(const Graph & graph, GraphStateHistory & states);
};

class KruskalAlgorithm : public Algorithm
{
protected:
    virtual void run(const Graph & graph, GraphStateHistory & states);
};

class PrimAlgorithm : public Algorithm
{
protected:
    virtual void run(const Graph & graph, GraphStateHistory & states);
};

class FloydWarshallAlgorithm : public Algorithm
{
protected:
    virtual void run(const Graph & graph, GraphStateHistory & states);
};
