#include "MainMenu.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Main Menu");
    window.setFramerateLimit(30);

    MainMenu mainMenu(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            mainMenu.handleInput(event);
        }

        window.clear();
        mainMenu.drawMainMenu();
        window.display();
    }

    return 0;
}