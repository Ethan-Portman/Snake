#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Segment.h"

class SnakeTextures {
private:
	const int blockWidth = 80;
	const int gameOffset = 40;

	sf::Texture snakeHead;
	sf::Texture snakeBody;
	sf::Texture snakeTail;
	sf::Texture snakeTurn;
	sf::Texture caterpillar;

	sf::Sprite snakeHeadSprite;
	sf::Sprite snakeBodySprite;
	sf::Sprite snakeTailSprite;
	sf::Sprite snakeTurnSprite;
	sf::Sprite caterpillarSprite;

	

public:
	// Load Sprites used for game
	SnakeTextures();

	// Get the Head Sprite of the Snake
	const sf::Sprite& getSnakeHead(int xOffset, int yOffset, Direction direction);

	// Get the Body Sprite of the Snake
	const sf::Sprite& getSnakeBody(int xOffset, int yOffset, Direction direction);

	// Get the Tail Sprite of the Snake
	const sf::Sprite& getSnakeTail(int xOffset, int yOffset, Direction direction);

	// Get the Turn Sprite of the Snake
	const sf::Sprite& getSnakeTurn(int xOffset, int yOffset, Direction direction);

	// Gets a any direction and type of snake part
	const sf::Sprite& getSnakePart(int xOffset, int yOffset, Direction direction, SnakePart snakepart);

	// Get a Caterpillar Sprite
	const sf::Sprite& getCaterpillar(int xOffset, int yOffset);
};

