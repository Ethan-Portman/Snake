#pragma once
enum class Direction { NORTH, SOUTH, EAST, WEST, 
					   NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST,
					   NONE };

enum class SnakePart {HEAD, BODY, TURN, TAIL};

class Segment {
private:
	SnakePart snakepart;
	Direction direction;
	int x;
	int y;
public:
	// Constructor
	Segment(Direction d, SnakePart sp, int x = 0, int y = 0)
		: direction(d), snakepart(sp), x(x), y(y)
	{}
	
	// Getters
	SnakePart getSnakePart() const { return snakepart; }
	Direction getDirection() const { return direction; }
	int getX() const { return x; }
	int getY() const { return y; }

	// Setters
	void setSnakepart(SnakePart sp) { snakepart = sp; }
	void setDirection(Direction d) { direction = d; }
	void updateX(int val) { x += val; }
	void updateY(int val) { y += val; }
	void updatePosition(int xVal, int yVal) { x = xVal; y = yVal; }

	bool isSameLocation(const Segment& other) const { return (x == other.x && y == other.y); }
};
