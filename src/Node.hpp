#pragma once

#include <SFML/System/Vector2.hpp>

class Node
{
public:
    static Node make(const sf::Vector2f & position);

    char label;
    sf::Vector2f position;

    Node();

    Node(const char label, const sf::Vector2f & position);

    static char currentLabel;
};

bool operator==(const Node & left, const Node & right);
