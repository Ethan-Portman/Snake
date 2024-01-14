#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window) 
    : window(window) 
{

    if (!arcadeFont.loadFromFile("Fonts/arcadeFont.ttf")) {
        std::cout << "Error loading arcadeFont.ttf\n";
    }

    // Create and configure button
    snakeButton.setSize(sf::Vector2f(320.f, 80.f));    // Set button size
    snakeButton.setFillColor(sf::Color::Transparent);  // Set fill color to Transparent
    snakeButton.setOutlineColor(sf::Color::Green);     // Set outline color
    snakeButton.setOutlineThickness(5.f);              // Set outline thickness
    snakeButton.setPosition(window.getSize().x / 2 - snakeButton.getSize().x / 2, window.getSize().y / 2 - snakeButton.getSize().y / 2);

    // Set up button text
    buttonText.setFont(arcadeFont);
    buttonText.setString("Snake");
    buttonText.setCharacterSize(60);
    buttonText.setFillColor(sf::Color::White);

    // Center the text on the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    buttonText.setPosition(snakeButton.getPosition().x + snakeButton.getSize().x / 2, snakeButton.getPosition().y + snakeButton.getSize().y / 2);

    // Set up welcome message
    welcomeText.setFont(arcadeFont);
    welcomeText.setString("Welcome to the Arcade!");
    welcomeText.setCharacterSize(80);
    welcomeText.setFillColor(sf::Color::White);

    // Center the welcome message
    sf::FloatRect welcomeBounds = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeBounds.left + welcomeBounds.width / 2.f, welcomeBounds.top + welcomeBounds.height / 2.f);
    welcomeText.setPosition(window.getSize().x / 2, window.getSize().y / 4);
}

void MainMenu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        if (snakeButton.getGlobalBounds().contains(mousePos)) {
            snakeButton.setOutlineColor(sf::Color::Red);
        }
        else {
            snakeButton.setOutlineColor(sf::Color::Green);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        if (snakeButton.getGlobalBounds().contains(mousePos)) {
            startSnake(window);
        }
    }
}

