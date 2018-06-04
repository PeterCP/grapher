#include "Graph.hpp"
#include <SFML/Graphics/CircleShape.hpp>

Graph::Graph()
{ }

Graph::Graph(const std::size_t nodeCount, const std::size_t edgeCount)
    : nodes(nodeCount)
    , edges(edgeCount)
{ }

Graph::Graph(const Graph & other)
    : nodes{ other.nodes }
    , edges{ other.edges }
{ }

Graph::Graph(Graph && other)
    : nodes{ std::move(other.nodes) }
    , edges{ std::move(other.edges) }
{ }

Graph & Graph::operator=(const Graph & other)
{
    if (this == &other)
        return *this;
    
    nodes = other.nodes;
    edges = other.edges;
    
    return *this;
}

Graph & Graph::operator=(Graph && other)
{
    if (this == &other)
        return *this;
    
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    
    return *this;
}

bool Graph::nodeAt(const sf::Vector2f & position, std::size_t & result) const
{
    sf::CircleShape circle{ 10 };
    circle.setOrigin({ 10, 10 });
    for (std::size_t i = 0; i < nodes.size(); i++) {
        circle.setPosition(nodes[i].position);
        if (circle.getGlobalBounds().contains(position)) {
            result = i;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<std::size_t, int>> Graph::neighborsOf(const std::size_t index) const
{
    std::vector<std::pair<std::size_t, int>> result;
    
    for (auto & edge : edges) {
        if (edge.a == index) {
            result.push_back({ edge.b, edge.weight });
        } else if (edge.b == index) {
            result.push_back({ edge.a, edge.weight });
        }
    }

    return std::move(result);
}
