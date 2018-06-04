#include <iostream>
#include <string>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "algorithms.hpp"
#include "display.hpp"
#include "Graph.hpp"
#include "GraphStateHistory.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "sfext.hpp"
#include "files.hpp"

const std::string FONT = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf";
const std::string SAVEFILE = "./graph.txt";
const std::string HELP =
"Mouse actions:\n\
	left click -> Add node to graph.\n\
	right click -> Select first node for edge creation.\n\
	right click again -> Select second node and create edge.\n\
Main keys:\n\
    s -> Save graph to file.\n\
    l -> Load graph from file.\n\
    c -> Clear graph.\n\
    h -> Show help.\n\
Algorithm keys:\n\
	d -> Run Dijkstra's algorithm.\n\
	f -> Run Floyd-Warshall's algorithm.\n\
	k -> Run Kruskal's algorithm.\n\
	p -> Run Prim's algorithm.";

sf::Font font;

int main()
{
	if (!font.loadFromFile(FONT)) {
		std::cerr << "Could not load font from '" << FONT << "'.";
		return 1;
	}

	sf::RenderWindow window{
		sf::VideoMode{ 1280, 720 },
		"Graph algorithm visualization.",
	};
	window.setFramerateLimit(60);

	Graph graph;

	// Used for selecting node pairs.
	bool gotSelected = false;
	std::size_t selectedIndex;

	if (window.isOpen()) {
		DisplayMessage(window, HELP, 2000);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					Node point = Node::make(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
					graph.nodes.push_back(point);
				} else if (event.mouseButton.button == sf::Mouse::Button::Right) {
					auto mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					std::size_t nodeIndex;
					if (graph.nodeAt(mousePosition, nodeIndex)) {
						if (gotSelected) {
							int weight = AskForWeight(window, font);
							graph.edges.push_back({ selectedIndex, nodeIndex, weight });
							gotSelected = false;
							selectedIndex = 0;
						} else {
							selectedIndex = nodeIndex;
							gotSelected = true;
						}
					}
				}
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::S) { // Save graph to file.
					try {
						SaveToFile(graph, SAVEFILE);
					} catch (std::exception ex) {
						DisplayMessage(window, "Could not write graph to file.", 2000);
					}
				} else if (event.key.code == sf::Keyboard::L) { // Load graph from file.
					try {
						graph = LoadFromFile(SAVEFILE);
						gotSelected = false;
						selectedIndex = 0;
					} catch (std::exception ex) {
						DisplayMessage(window, "Could not read graph from file.", 2000);
					}
				} else if (event.key.code == sf::Keyboard::C) { // Clear graph.
					graph = Graph();
					Node::currentLabel = 'A';
					gotSelected = false;
					selectedIndex = 0;
				} else if (event.key.code == sf::Keyboard::H) { // Show help.
					DisplayMessage(window, HELP, 2000);
				} else if (event.key.code == sf::Keyboard::D) { // Run Dijkstra's algorithm.
					DijkstraAlgorithm algorithm;
					GraphStateHistory states = algorithm(graph);
					DrawAlgorithmHistory(window, graph, states, 500);
				} else if (event.key.code == sf::Keyboard::F) { // Run Floyd-Warshall's algorithm.
					FloydWarshallAlgorithm algorithm;
					GraphStateHistory states = algorithm(graph);
					DrawAlgorithmHistory(window, graph, states, 500);
				} else if (event.key.code == sf::Keyboard::K) { // Run Kruskal's algorithm.
					KruskalAlgorithm algorithm;
					GraphStateHistory states = algorithm(graph);
					DrawAlgorithmHistory(window, graph, states, 500);
				} else if (event.key.code == sf::Keyboard::P) { // Run Prim's algorithm.
					PrimAlgorithm algorithm;
					GraphStateHistory states = algorithm(graph);
					DrawAlgorithmHistory(window, graph, states, 500);
				}
			}
		}

		window.clear(sf::Color::White);

		// Draw edges.
		sf::LineShape line;
		line.setFillColor(sf::Color::Black);
		line.setThickness(3);
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Black);
		for (auto & edge : graph.edges) {
			const sf::Vector2f & start = graph.nodes[edge.a].position,
				finish = graph.nodes[edge.b].position;
			line.setStart(start);
			line.setFinish(finish);
			window.draw(line);

			text.setPosition({
				(start.x + finish.x) / 2,
				(start.y + finish.y) / 2
			});
			text.setString(std::to_string(edge.weight));
			window.draw(text);
		}

		// Draw nodes.
		sf::CircleShape circle{ 10 };
		circle.setOrigin({10, 10});
		circle.setOutlineThickness(2);
		circle.setOutlineColor(sf::Color::Black);
		for (std::size_t i = 0; i < graph.nodes.size(); i++) {
			if (gotSelected && i == selectedIndex) {
				circle.setFillColor(sf::Color::Green);
			} else {
				circle.setFillColor(sf::Color::Red);
			}
			circle.setPosition(graph.nodes[i].position);
			window.draw(circle);

			text.setPosition(graph.nodes[i].position);
			text.setString(graph.nodes[i].label);
			window.draw(text);
		}

		window.display();
	}

	return 0;
}
