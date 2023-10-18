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
	const sf::Vector2<float> TILE_SIZE = sf::Vector2<float>(32, 32);
	Board();
	Board(const sf::Vector2<int>& boardSize);
	const sf::Vector2<int>& getBoardSize() const;
	const Tile& getTile(const sf::Vector2<float>& exactPosition) const;
	const Tile& getTile(const sf::Vector2<int>& boardPosition) const;

	//bomb tools
	void clearBombs();
	void assignRandomBombs(const unsigned int& numBombs);
	void assignSpecificBombs(const std::string& setup);
	void setBombVisibility(const bool& value);
	const bool& getBombVisibility() const;

	//misc tools
	const sf::Vector2<int>& getTileIndexFromExactPosition(const sf::Vector2<float>& exactPosition) const;
	void drawBoard(sf::RenderWindow* window);
	const bool& checkWin() const;

	//interpret input
	const ClickResult& interpretMouseClick(sf::Event event);

	~Board();
private:
	sf::Vector2<int> boardSize;
	unsigned int numTiles;

	GreyTile** tileArr;
	FlagTile** flagArr;
	DebugBombTile* debugBombArr;

	Counter counter;

	unsigned int numBombs;
	bool bombsVisible;
};