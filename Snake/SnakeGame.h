#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Bugs.h"

struct Point {
	int x;
	int y;
};

class SnakeGame : public SnakeTextures {
private:
	/*------------------ WINDOW VARIABLES ------------------*/
	sf::RenderWindow& window;
	double secondsPerTick = 0.3;   
	double secondsSinceLastTick{ 0.0 };	
	const int numRows = 20;     
	const int numCols = 20;     
	const int cellSize = 40;    

	/*------------------- GAME VARIABLES -------------------*/
	const int bugsInGame = 25;
	int bugsAte{ 0 };
	Snake snake;                
	Bugs bugList;
	
public:
	SnakeGame(sf::RenderWindow& window);

	void updateBugsOnBoard();

	void drawCurrentState(sf::RenderWindow& window);

	bool forageAndEat();

	void moveSnake();

	void updateSnakeDirection(Direction d);

	Point getUnoccupiedPoint();

	void processGameLoop(float secondsSinceLastLoop);

	void registerMovement(const sf::Event& event);
};

