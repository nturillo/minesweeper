#pragma once

#include <SFML/Graphics.hpp>
#include "GreyTile.h"
#include "FlagTile.h"
#include  "DebugBombTile.h"
#include "Counter.h"
#include "Random.h"


class Board
{
public:
	enum ClickResult {
		WIN, LOSE, NEUTRAL
	};
	const sf::Vector2f TILE_SIZE = sf::Vector2f(32, 32);
	Board();
	Board(const sf::Vector2i& boardSize);
	const sf::Vector2i& getBoardSize() const;
	const Tile& getTile(const sf::Vector2f& exactPosition) const;
	const Tile& getTile(const sf::Vector2i& boardPosition) const;

	//bomb tools
	void clearBombs();
	void assignRandomBombs(const unsigned int numBombs);
	void assignSpecificBombs(const std::string& setup);
	void setBombVisibility(const bool value);
	const bool getBombVisibility() const;

	//misc tools
	const sf::Vector2i& getTileIndexFromExactPosition(const sf::Vector2f& exactPosition) const;
	void drawBoard(sf::RenderWindow* window);
	const bool checkWin() const;

	//interpret input
	const ClickResult& interpretMouseClick(sf::Event event);

	~Board();
private:
	sf::Vector2i boardSize;
	unsigned int numTiles;

	GreyTile** tileArr;
	FlagTile** flagArr;
	DebugBombTile* debugBombArr;

	Counter counter;

	unsigned int numBombs;
	bool bombsVisible;
};