#pragma once
#include <vector>
#include "SnakeTextures.h"
#include "Segment.h"

class Snake{
private:
	int length;
	std::vector<Segment> snakeSegments;
	bool isAlive;
	Direction snakeDirection;
	int mousesEaten;
	bool turnOccurred{ false };


public:
	// Constructor
	Snake();


	// Getters
	const std::vector<Segment>& getLocs() const {return snakeSegments;}
	Direction getDirection() { return snakeDirection; }
	int getLength() const { return length; }
	Segment getHeadSegment() { return snakeSegments[0]; }

	// Change Snake Direction
	void changeDirection(Direction d);

	// Update Head Segment to proper direction of Snake
	void updateHeadSegment();

	// Update rest of Snake to align with head
	void updateSnakeLocs();

    // Get a direction with a single turn involved
    Direction getSingleTurnDirection(Direction childDirection, Direction parentDirection);

    // Get a direction with a U-turn involved
    Direction getUTurnDirection(Direction child, Direction current, Direction parent);

    // Get a direction with a S-turn involved
    Direction getSTurnDirection(Direction parent, Direction current);

    // Retrieves a smoothed out version of the snake ready for printing
	std::vector<Segment> getSmoothSnake();

	void grow() {
		Direction tailDirection = snakeSegments[length - 1].getDirection();
		int newSegmentX = snakeSegments[length - 1].getX();
		int newSegmentY = snakeSegments[length - 1].getY();

		if (tailDirection == Direction::NORTH) 
			newSegmentY++;

		else if (tailDirection == Direction::SOUTH) 
			newSegmentY--;
		else if (tailDirection == Direction::EAST) 
			newSegmentX--;
		else if (tailDirection == Direction::WEST) 
			newSegmentX++;
		
		snakeSegments[length - 1].setSnakepart(SnakePart::BODY);
		snakeSegments.push_back(Segment{ tailDirection , SnakePart::TAIL, newSegmentX, newSegmentY });
		length++;
	}
	
	
	
	void checkForSelfContact() const;

	void strollAlong() {
		updateHeadSegment();
		updateSnakeLocs();
	}

	bool occupies(int x, int y) {
		for (const Segment& seg : snakeSegments) {
			if (seg.getX() == x && seg.getY() == y)
				return true;
		}
		return false;
	}
};

