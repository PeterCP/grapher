#include "Node.hpp"

char Node::currentLabel = 'A';

Node Node::make(const sf::Vector2f & position)
{
	return Node(currentLabel++, position);
}

Node::Node()
	: label('A')
	, position()
{ }

Node::Node(const char label, const sf::Vector2f & position)
	: label{ label }
	, position{ position }
{ }

bool operator==(const Node & left, const Node & right)
{
	return left.label == right.label;
}
