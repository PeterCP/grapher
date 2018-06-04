#include "Edge.hpp"

Edge::Edge()
    : a()
    , b()
    , weight()
{ }

Edge::Edge(std::size_t a, std::size_t b, int weight)
    : a{ a }
    , b{ b }
    , weight{ weight }
{ }

bool operator==(const Edge & left, const Edge & right)
{
    return left.a == right.a
        && left.b == right.b
        && left.weight == right.weight;
}
