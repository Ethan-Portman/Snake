#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SnakeGame.h"


class MainMenu {
private:
    sf::RenderWindow& window;       
    sf::RectangleShape snakeButton;
    sf::Text buttonText;
    sf::Text welcomeText;
    sf::Font arcadeFont;

public:
    MainMenu(sf::RenderWindow& window);

    void handleInput(sf::Event& event);

    void drawMainMenu() {
        window.draw(welcomeText);
        window.draw(snakeButton);
        window.draw(buttonText);
    }

    void startSnake(sf::RenderWindow& window) {
        SnakeGame game(window);
        sf::Clock clock;

        while (window.isOpen()) {
            float elapsedTime = clock.getElapsedTime().asSeconds();
            clock.restart();
            sf::Event event;

            // 1. Listen for any events and register them.
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    game.registerMovement(event);
                }
            }
            // 2. If enough time has passed, process the game loop
            game.processGameLoop(elapsedTime);
        }
    }
};