#include "Snake.h"

Snake::Snake() : length(6), isAlive(true), snakeDirection(Direction::NORTH), mousesEaten(0)
{
	snakeSegments = { Segment(snakeDirection, SnakePart::HEAD, 10, 10),
			 Segment(snakeDirection, SnakePart::BODY, 10, 11),
			 Segment(snakeDirection, SnakePart::BODY, 10, 12),
			 Segment(snakeDirection, SnakePart::BODY, 10, 13),
			 Segment(snakeDirection, SnakePart::BODY, 10, 14),
			 Segment(snakeDirection, SnakePart::TAIL, 10, 15) };
}

void Snake::changeDirection(Direction d) {
	if (d == Direction::NORTH && snakeSegments[0].getDirection() != Direction::SOUTH)
		snakeDirection = d;
	if (d == Direction::EAST && snakeSegments[0].getDirection() != Direction::WEST)
		snakeDirection = d;
	if (d == Direction::SOUTH && snakeSegments[0].getDirection() != Direction::NORTH)
		snakeDirection = d;
	if (d == Direction::WEST && snakeSegments[0].getDirection() != Direction::EAST) {
		snakeDirection = d;
	}
}

void Snake::updateHeadSegment() {
	int headX = snakeSegments[0].getX();
	int headY = snakeSegments[0].getY();

	if (snakeDirection == Direction::NORTH) {
		if (headY == 0) { headY = 20; }
		headY--;
	}
	if (snakeDirection == Direction::SOUTH) {
		if (headY == 19) { headY = -1; }
		headY++;
	}
	if (snakeDirection == Direction::EAST) {
		if (headX == 19) { headX = -1; }
		headX++;
	}
	if (snakeDirection == Direction::WEST) {
		if (headX == 0) { headX = 20; }
		headX--;
	}

	snakeSegments[0].setDirection(snakeDirection);
	snakeSegments[0].updatePosition(headX, headY);
}

void Snake::updateSnakeLocs() {
	Direction parentDirection = snakeDirection;

	for (int i = 1; i < length; i++) {
		Direction currentDirection = snakeSegments[i].getDirection();
		int currX = snakeSegments[i].getX();
		int currY = snakeSegments[i].getY();

		if (currentDirection == Direction::NORTH) {
			if (currY == 0) { currY = 20; }
			currY--;
		}
		else if (currentDirection == Direction::SOUTH) {
			if (currY == 19) { currY = -1; }
			currY++;
		}
		if (currentDirection == Direction::EAST) {
			if (currX == 19) { currX = -1; }
			currX++;
		}
		else if (currentDirection == Direction::WEST) {
			if (currX == 0) { currX = 20; }
			currX--;
		}

		snakeSegments[i].setDirection(parentDirection);
		snakeSegments[i].updatePosition(currX, currY);
		parentDirection = currentDirection;
	}
}

Direction Snake::getSingleTurnDirection(Direction childDirection, Direction parentDirection) {
	Direction d = Direction::NONE;

	if (parentDirection == Direction::WEST)
		d = (childDirection == Direction::NORTH) ? Direction::NORTHWEST : Direction::SOUTHWEST;
	if (parentDirection == Direction::EAST)
		d = (childDirection == Direction::NORTH) ? Direction::NORTHEAST : Direction::SOUTHEAST;
	if (parentDirection == Direction::NORTH)
		d = (childDirection == Direction::WEST) ? Direction::SOUTHEAST : Direction::SOUTHWEST;
	if (parentDirection == Direction::SOUTH)
		d = (childDirection == Direction::WEST) ? Direction::NORTHEAST : Direction::NORTHWEST;

	return d;
}

Direction Snake::getUTurnDirection(Direction child, Direction current, Direction parent) {
	Direction d = Direction::NONE;

	if (parent == Direction::SOUTH && child == Direction::NORTH)
		d = (current == Direction::WEST) ? Direction::NORTHWEST : Direction::NORTHEAST;
	else if (parent == Direction::NORTH && child == Direction::SOUTH)
		d = (current == Direction::WEST) ? Direction::SOUTHWEST : Direction::SOUTHEAST;
	else if (parent == Direction::WEST && child == Direction::EAST)
		d = (current == Direction::NORTH) ? Direction::SOUTHWEST : Direction::NORTHWEST;
	else if (parent == Direction::EAST && child == Direction::WEST)
		d = (current == Direction::NORTH) ? Direction::SOUTHEAST : Direction::NORTHEAST;

	return d;
}

Direction Snake::getSTurnDirection(Direction parent, Direction current) {
	Direction d = Direction::NONE;

	if (parent == Direction::NORTH)
		d = (current == Direction::WEST) ? Direction::NORTHWEST : Direction::NORTHEAST;
	else if (parent == Direction::SOUTH)
		d = (current == Direction::WEST) ? Direction::SOUTHWEST : Direction::SOUTHEAST;
	else if (parent == Direction::EAST)
		d = (current == Direction::NORTH) ? Direction::SOUTHWEST : Direction::NORTHWEST;
	else if (parent == Direction::WEST)
		d = (current == Direction::NORTH) ? Direction::SOUTHEAST : Direction::NORTHEAST;

	return d;
}

std::vector<Segment> Snake::getSmoothSnake() {
	std::vector<Segment> smoothedSegments;
	smoothedSegments.push_back(snakeSegments[0]);

	Direction parentDirection = snakeSegments[0].getDirection();
	for (int i = 1; i < length - 1; i++) {
		Direction currentDirection = snakeSegments[i].getDirection();
		Direction childDirection = snakeSegments[i + 1].getDirection();
		Direction newDirection = currentDirection;
		bool turnHappened = false;

		// Single Turn
		if (parentDirection != childDirection && parentDirection == currentDirection) {
			turnHappened = true;
			newDirection = getSingleTurnDirection(childDirection, parentDirection);
		}
		// U Turn
		else if (parentDirection != currentDirection && currentDirection != childDirection && parentDirection != childDirection) {
			turnHappened = true;
			newDirection = getUTurnDirection(childDirection, currentDirection, parentDirection);
		}
		// Double Turn Straight
		else if (parentDirection != currentDirection && currentDirection != childDirection && parentDirection == childDirection) {
			turnHappened = true;
			newDirection = getSTurnDirection(parentDirection, currentDirection);
		}

		if (turnHappened) {
			Segment turnSegment{ newDirection, SnakePart::TURN, snakeSegments[i].getX(), snakeSegments[i].getY() };
			smoothedSegments.push_back(turnSegment);
		}
		else {
			Segment repeatSegment{ currentDirection, SnakePart::BODY, snakeSegments[i].getX(), snakeSegments[i].getY() };
			smoothedSegments.push_back(repeatSegment);
		}
		parentDirection = currentDirection;
	}

	// Add the last segment
	smoothedSegments.push_back(snakeSegments[length - 1]);
	return smoothedSegments;
}


void Snake::checkForSelfContact() const {
	for (int i = 0; i < length - 1; i++) {
		Segment currSegment = snakeSegments[i];
		for (int j = i + 1; j < length; j++) {
			Segment segment = snakeSegments[j];
			if (currSegment.isSameLocation(segment) && i != j) {
				throw std::runtime_error("Snake Collision!");
			}
		}
	}
}