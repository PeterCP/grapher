#pragma once

#include <cstddef>

class Edge
{
public:

    std::size_t a, b;
    int weight;

    Edge();

    Edge(std::size_t a, std::size_t b, int weight);
};

bool operator==(const Edge & a, const Edge & b);
