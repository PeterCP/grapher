#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Edge.hpp"
#include "Node.hpp"

class Graph
{
public:
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    Graph();

    Graph(const std::size_t nodeCount, const std::size_t edgeCount);

    Graph(const Graph & other);

    Graph(Graph && other);

    Graph & operator=(const Graph & other);

    Graph & operator=(Graph && other);

    bool nodeAt(const sf::Vector2f & position, std::size_t & result) const;

    std::vector<std::pair<std::size_t, int>> neighborsOf(const std::size_t index) const;
};
