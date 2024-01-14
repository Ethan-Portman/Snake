#include "SnakeTextures.h"

SnakeTextures::SnakeTextures() {
	if (!snakeHead.loadFromFile("Images/SnakeHead.png")) {
		std::cout << "Error loading Snake Head Texture\n";
	}

	if (!snakeBody.loadFromFile("Images/SnakeBody.png")) {
		std::cout << "Error loading Snake Body Texture\n";
	}

	if (!snakeTail.loadFromFile("Images/SnakeTail.png")) {
		std::cout << "Error loading Snake Tail Texture\n";
	}

	if (!snakeTurn.loadFromFile("Images/SnakeTurn.png")) {
		std::cout << "Error loading Snake Turn Texture\n";
	}

	if (!caterpillar.loadFromFile("Images/Caterpillar.png")) {
		std::cout << "Error loading Caterpillar Texture\n";
	}

	snakeHeadSprite.setTexture(snakeHead);
	snakeHeadSprite.scale(sf::Vector2f(2.0f, 2.0f));
	snakeHeadSprite.setOrigin(20.f, 20.f);

	snakeBodySprite.setTexture(snakeBody);
	snakeBodySprite.scale(sf::Vector2f(2.0f, 2.0f));
	snakeBodySprite.setOrigin(11.f, 19.5f);

	snakeTailSprite.setTexture(snakeTail);
	snakeTailSprite.scale(sf::Vector2f(2.0f, 2.0f));
	snakeTailSprite.setOrigin(11.f, 19.5f);

	snakeTurnSprite.setTexture(snakeTurn);
	snakeTurnSprite.scale(sf::Vector2f(2.0f, 2.0f));
	snakeTurnSprite.setOrigin(11.5f, 11.5f);

	caterpillarSprite.setTexture(caterpillar);
	caterpillarSprite.scale(sf::Vector2f(1.5f, 1.5f));
}

const sf::Sprite& SnakeTextures::getSnakeHead(int xOffset, int yOffset, Direction direction) {
	int xPos = xOffset * blockWidth + gameOffset;
	int yPos = yOffset * blockWidth + gameOffset;

	if (direction == Direction::NORTH)
		snakeHeadSprite.setRotation(180);
	if (direction == Direction::WEST)
		snakeHeadSprite.setRotation(90);
	if (direction == Direction::EAST)
		snakeHeadSprite.setRotation(-90);
	if (direction == Direction::SOUTH)
		snakeHeadSprite.setRotation(0);

	snakeHeadSprite.setPosition(sf::Vector2f(xPos, yPos));
	return snakeHeadSprite;
}

const sf::Sprite& SnakeTextures::getSnakeBody(int xOffset, int yOffset, Direction direction) {
	int xPos = xOffset * blockWidth + gameOffset;
	int yPos = yOffset * blockWidth + gameOffset;

	if (direction == Direction::NORTH)
		snakeBodySprite.setRotation(180);
	if (direction == Direction::WEST)
		snakeBodySprite.setRotation(90);
	if (direction == Direction::EAST)
		snakeBodySprite.setRotation(-90);
	if (direction == Direction::SOUTH)
		snakeBodySprite.setRotation(0);

	snakeBodySprite.setPosition(sf::Vector2f(xPos, yPos));
	return snakeBodySprite;
}

const sf::Sprite& SnakeTextures::getSnakeTail(int xOffset, int yOffset, Direction direction) {
	int xPos = xOffset * blockWidth + gameOffset;
	int yPos = yOffset * blockWidth + gameOffset;

	if (direction == Direction::NORTH)
		snakeTailSprite.setRotation(0);
	if (direction == Direction::WEST)
		snakeTailSprite.setRotation(-90);
	if (direction == Direction::EAST)
		snakeTailSprite.setRotation(90);
	if (direction == Direction::SOUTH)
		snakeTailSprite.setRotation(180);

	snakeTailSprite.setPosition(sf::Vector2f(xPos, yPos));
	return snakeTailSprite;
}

const sf::Sprite& SnakeTextures::getSnakeTurn(int xOffset, int yOffset, Direction direction) {
	int xPos = xOffset * blockWidth + gameOffset;
	int yPos = yOffset * blockWidth + gameOffset;

	if (direction == Direction::NORTHEAST) // Correct |-
		snakeTurnSprite.setRotation(0);
	if (direction == Direction::NORTHWEST) // Correct -|
		snakeTurnSprite.setRotation(90);
	if (direction == Direction::SOUTHEAST) // Correct |_
		snakeTurnSprite.setRotation(-90);
	if (direction == Direction::SOUTHWEST) // Correct _|
		snakeTurnSprite.setRotation(180);



	snakeTurnSprite.setPosition(sf::Vector2f(xPos, yPos));
	return snakeTurnSprite;
}

const sf::Sprite& SnakeTextures::getSnakePart(int xOffset, int yOffset, Direction direction, SnakePart snakepart) {
	if (snakepart == SnakePart::HEAD) {
		return getSnakeHead(xOffset, yOffset, direction);
	}
	else if (snakepart == SnakePart::BODY) {
		return getSnakeBody(xOffset, yOffset, direction);
	}
	else if (snakepart == SnakePart::TURN) {
		return getSnakeTurn(xOffset, yOffset, direction);
	}
	else {
		return getSnakeTail(xOffset, yOffset, direction);
	}
}

const sf::Sprite& SnakeTextures::getCaterpillar(int xOffset, int yOffset) {
	int xPos = xOffset * blockWidth + 10;
	int yPos = yOffset * blockWidth + 10;

	caterpillarSprite.setPosition(sf::Vector2f(xPos, yPos));
	return caterpillarSprite;
}