#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Board.h"
#include "Counter.h"




class Game
{
public:
	const unsigned int LOWER_MARGIN = 100;
	Game();
	void Start(const sf::Vector2<int>& boardSize, const unsigned int& numBombs);
	const bool& Process();
	~Game();
private:
	sf::RenderWindow* window = nullptr;
	Board* board = nullptr;

	bool isRunning;
	bool isAlive;

	Button restartButton;
	Button debugButton;
	Button testButtons[3];
};

