#include "SnakeGame.h"

SnakeGame::SnakeGame(sf::RenderWindow& window)
	: window(window)
{
	while (bugList.size() < bugsInGame) {
		Point p = getUnoccupiedPoint();
		bugList.addBug(p.x, p.y);
	}
}

void SnakeGame::updateBugsOnBoard() {
	while (bugList.size() < bugsInGame) {
		Point p = getUnoccupiedPoint();
		bugList.addBug(p.x, p.y);
	}
}

void SnakeGame::drawCurrentState(sf::RenderWindow& window) {
	// Draw all the bugs
	for (const Bug& b : bugList.getBugs()) {
		sf::Sprite caterpillar = getCaterpillar(b.x, b.y);
		window.draw(caterpillar);
	}

	// Draw the Snake
	for (const Segment& segment : snake.getSmoothSnake()) {
		sf::Sprite snakeSegment = getSnakePart(segment.getX(), segment.getY(), segment.getDirection(), segment.getSnakePart());
		window.draw(snakeSegment);
	}
}

bool SnakeGame::forageAndEat() {
	Segment headOfSnake = snake.getHeadSegment();
	if (bugList.removeBug(headOfSnake.getX(), headOfSnake.getY())) {
		bugsAte++;
		snake.grow();
		return true;
	}
	return false;
}

void SnakeGame::moveSnake() {
	snake.strollAlong();
	snake.checkForSelfContact();
	forageAndEat();
	updateBugsOnBoard();
}

Point SnakeGame::getUnoccupiedPoint() {
	while (true) {
		int x = std::rand() % 21;
		int y = std::rand() % 21;
		if (bugList.spotTaken(x, y) || snake.occupies(x, y))
			continue;

		return Point{ x, y };
	}
}

void SnakeGame::processGameLoop(float secondsSinceLastLoop) {
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick > secondsPerTick) {
		secondsSinceLastTick -= secondsPerTick;
		moveSnake();
		window.clear();
		drawCurrentState(window);
		window.display();
	}
}

void SnakeGame::updateSnakeDirection(Direction d) {
	snake.changeDirection(d);
}

void SnakeGame::registerMovement(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			updateSnakeDirection(Direction::NORTH);
			break;
		case sf::Keyboard::Left:
			updateSnakeDirection(Direction::WEST);
			break;
		case sf::Keyboard::Right:
			updateSnakeDirection(Direction::EAST);
			break;
		case sf::Keyboard::Down:
			updateSnakeDirection(Direction::SOUTH);
			break;
		}
	}
}