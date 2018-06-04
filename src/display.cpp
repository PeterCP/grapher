#include "display.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "sfext.hpp"

extern sf::Font font;

int AskForWeight(sf::RenderWindow & window, sf::Font & font)
{
    std::string str;
    sf::Text text;
    sf::Event event;

    text.setPosition({ 20, 20 });
    text.setFont(font);

    while (window.isOpen())
    {
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                using Kb = sf::Keyboard;
                Kb::Key code = event.key.code;
                if (code >= Kb::Num0 && code <= Kb::Num9) {
                    char c = code - Kb::Num0 + '0';
                    str.push_back(c);
                } else if (code == Kb::BackSpace && str.size() > 0) {
                    str.pop_back();
                } else if (code == Kb::Return) {
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        std::string message = "Weight for edge: " + str;
        text.setString(message);
        window.draw(text);

        window.display();
    }

    return std::stoi(str);
}

void DisplayMessage(sf::RenderWindow & window, const std::string & message, const int millis)
{
    if (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event) && event.type == sf::Event::Closed) {
            window.close();
        } else {
            sf::Text text;
            text.setPosition({ 20, 20 });
            text.setFont(font);
            text.setString(message);

            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(millis));
        }
    }
}

void DrawGraphState(sf::RenderWindow & window, const Graph & graph, const GraphState & state);

void DrawAlgorithmHistory(sf::RenderWindow & window, const Graph & graph,
                          const GraphStateHistory & history, const int delay)
{
    for (auto & state : history.states) {
        DrawGraphState(window, graph, state);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void DrawGraphState(sf::RenderWindow & window, const Graph & graph, const GraphState & state)
{
    window.clear(sf::Color::White);

    // Draw edges.
    sf::Text text;
    sf::LineShape line;
    line.setThickness(3);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    for (std::size_t i = 0; i < graph.edges.size(); i++) {
        if (state.exploredEdges[i]) {
            line.setFillColor(sf::Color::Red);
        } else {
            line.setFillColor(sf::Color::Black);
        }

        const sf::Vector2f & start = graph.nodes[graph.edges[i].a].position,
            finish = graph.nodes[graph.edges[i].b].position;

        line.setStart(start);
        line.setFinish(finish);
        window.draw(line);

        text.setPosition({
            (start.x + finish.x) / 2,
            (start.y + finish.y) / 2
        });
        text.setString(std::to_string(graph.edges[i].weight));
        window.draw(text);
    }

    // Draw nodes.
    sf::CircleShape circle{ 10 };
    circle.setOrigin({10, 10});
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Black);
    for (std::size_t i = 0; i < graph.nodes.size(); i++) {
        if (state.exploredNodes[i]) {
            circle.setFillColor(sf::Color::Red);
        } else {
            circle.setFillColor(sf::Color::Black);
        }
        circle.setPosition(graph.nodes[i].position);
        window.draw(circle);

        text.setPosition(graph.nodes[i].position);
        text.setString(graph.nodes[i].label);
        window.draw(text);
    }

    window.display();
}
