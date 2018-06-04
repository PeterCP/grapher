#pragma once

#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphStateHistory.hpp"

int AskForWeight(sf::RenderWindow & window, sf::Font & font);

void DisplayMessage(sf::RenderWindow & window, const std::string & message,
                    const int time);

void DrawAlgorithmHistory(sf::RenderWindow & window, const Graph & graph,
                          const GraphStateHistory & history, const int delay);
