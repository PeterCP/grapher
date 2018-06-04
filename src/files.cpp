#include "files.hpp"
#include <fstream>

void SaveToFile(const Graph & graph, const std::string & path)
{
    std::ofstream file(path);

    file << graph.nodes.size() << ' '
         << graph.edges.size() << ' '
         << Node::currentLabel << '\n';

    for (auto & node : graph.nodes) {
        file << node.label << ' '
             << node.position.x << ' '
             << node.position.y << '\n';
    }

    for (auto & edge : graph.edges) {
        file << edge.a << ' '
             << edge.b << ' '
             << edge.weight << '\n';
    }
}

Graph LoadFromFile(const std::string & path)
{
    std::ifstream file(path);

    std::size_t nodeCount, edgeCount;
    file >> nodeCount
         >> edgeCount
         >> Node::currentLabel;
    
    Graph graph(nodeCount, edgeCount);

    for (auto & node : graph.nodes) {
        file >> node.label
             >> node.position.x
             >> node.position.y;
    }

    for (auto & edge : graph.edges) {
        file >> edge.a
             >> edge.b
             >> edge.weight;
    }

    return graph;
}
