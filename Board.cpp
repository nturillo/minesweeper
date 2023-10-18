#include "Board.h"
#include <cstdlib>

Board::Board() {
	boardSize = sf::Vector2i(1, 1);

	tileArr = new GreyTile*[1];
	tileArr[0] = new GreyTile[1];
	tileArr[0][0] = GreyTile();

	flagArr = nullptr;

	numBombs = 0;
	debugBombArr = nullptr;
	bombsVisible = false;
}

Board::Board(const sf::Vector2i& boardSize) {
	this->boardSize = boardSize;
	numTiles = boardSize.x * boardSize.y;
	counter.setPosition(sf::Vector2f(0, boardSize.y * TILE_SIZE.y));

	//create array container for each row array
	tileArr = new GreyTile*[boardSize.y];
	
	//Fill tileArr with tiles, and set their sprites and textures and positions
	for (int y = 0; y < boardSize.y; y++) {
		//create array for each row
		tileArr[y] = new GreyTile[boardSize.x];
		for (int x = 0; x < boardSize.x; x++) {
			//set info for each tile in the row
			sf::Vector2i boardPosition = sf::Vector2i(x, y);
			tileArr[y][x].setBoardPosition(boardPosition);
			tileArr[y][x].setTexture(TextureManager::getTexture("tile_hidden"), 0);
			tileArr[y][x].setTileSize(TILE_SIZE);
		}
	}

	//Fill flagArr with tiles
	flagArr = new FlagTile*[boardSize.y];
	for (int y = 0; y < boardSize.y; y++) {
		//create array for each row
		flagArr[y] = new FlagTile[boardSize.x];
		for (int x = 0; x < boardSize.x; x++) {
			//set info for each tile in the row
			sf::Vector2i boardPosition = sf::Vector2i(x, y);
			flagArr[y][x].setBoardPosition(boardPosition);
			flagArr[y][x].setTileSize(TILE_SIZE);
		}
	}

	//Assign each tile's neighbor
	for (int x = 0; x < boardSize.x; x++) {
		for (int y = 0; y < boardSize.y; y++) {
			for (int i = 0; i < 8; i++) {
				//store info about where neighbors are in an unsigned char
				//some evil bitwise stuff here
				unsigned char neighborInfo = 255;
				if (x == 0) {
					neighborInfo = neighborInfo & 227;
				}
				if (x == boardSize.x - 1) {
					neighborInfo = neighborInfo & 62;
				}
				if (y == 0) {
					neighborInfo = neighborInfo & 143;
				}
				if (y == boardSize.y - 1) {
					neighborInfo = neighborInfo & 248;
				}
				//if (x == 0 && y == 0) {
				//	std::cout << (int)neighborInfo << std::endl;
				//}
				//Now, set each neighbor pointer accordingly
				if ((neighborInfo & (128 >> i)) == (128 >> i)) {
					int xIndex = x;
					int yIndex = y;
					if (i < 2 || i > 6) {
						xIndex++;
					}
					if (i > 2 && i < 6) {
						xIndex--;
					}
					if (i > 4) {
						yIndex++;
					}
					if (i > 0 && i < 4) {
						yIndex--;
					}
					tileArr[y][x].setNeighbor(i, &tileArr[yIndex][xIndex]);
				}
			}
		}
	}

	numBombs = 0;
	debugBombArr = nullptr;
	bombsVisible = false;
}

const sf::Vector2i& Board::getBoardSize() const {
	return boardSize;
}

const Tile& Board::getTile(const sf::Vector2f& exactPosition) const{
	sf::Vector2i tileIndex = getTileIndexFromExactPosition(exactPosition);
	return tileArr[tileIndex.y][tileIndex.x];
}

const Tile& Board::getTile(const sf::Vector2i& boardPosition) const {
	return tileArr[boardPosition.y][boardPosition.x];
}


//Bomb Tools
void Board::clearBombs() {
	//clear bombs
	for (int i = 0; i < numBombs; i++) {
		tileArr[debugBombArr[i].getBoardPosition().y][debugBombArr[i].getBoardPosition().x].setIsBomb(false);
		tileArr[debugBombArr[i].getBoardPosition().y][debugBombArr[i].getBoardPosition().x].setSpriteState(Tile::UNDER);
	}

	delete[] debugBombArr;
	numBombs = 0;
}

void Board::assignRandomBombs(const unsigned int numBombs) {
	clearBombs();

	this->numBombs = numBombs;
	debugBombArr = new DebugBombTile[numBombs];

	for (unsigned int i = 0; i < numBombs; ) {
		int x = Random::Int(0, boardSize.x - 1);
		int y = Random::Int(0, boardSize.y - 1);
		if (tileArr[y][x].getIsBomb()) {
			continue;
		}
		else {
			tileArr[y][x].setIsBomb(true);
			tileArr[y][x].setTexture(TextureManager::getTexture("mine"), 1);
			//tileArr[y][x].setSpriteState(Tile::BOTH); //temporary for debugging
			debugBombArr[i].setBoardPosition(sf::Vector2i(x, y));
			debugBombArr[i].setTexture(TextureManager::getTexture("mine"), 0);
			i++;
		}
	}

	counter.setNumber(numBombs);
}

void Board::assignSpecificBombs(const std::string& setup) {
	clearBombs();

	for (int i = 0; i < setup.size(); i++) {
		if (setup[i] == '1') {
			numBombs++;
		}
	}

	debugBombArr = new DebugBombTile[numBombs];
	unsigned int index = 0;
	unsigned int tempBombCounter = 0;
	for (int y = 0; y < boardSize.y; y++) {
		for (int x = 0; x < boardSize.x; x++) {
			if (setup[index] == '1') {
				tileArr[y][x].setIsBomb(true);
				tileArr[y][x].setTexture(TextureManager::getTexture("mine"), 1);
				debugBombArr[tempBombCounter].setBoardPosition(sf::Vector2i(x, y));
				debugBombArr[tempBombCounter].setTexture(TextureManager::getTexture("mine"), 0);
				tempBombCounter++;
			}
			index++;
		}
	}

	counter.setNumber(numBombs);
}

void Board::setBombVisibility(const bool value) {
	bombsVisible = value;
}

const bool Board::getBombVisibility() const {
	return bombsVisible;
}



//MISC TOOLS
const sf::Vector2i& Board::getTileIndexFromExactPosition(const sf::Vector2f& exactPosition) const {
	int x_pos = (int)exactPosition.x / TILE_SIZE.x;
	int y_pos = (int)exactPosition.y / TILE_SIZE.y;
	return sf::Vector2i(x_pos, y_pos);
}

void Board::drawBoard(sf::RenderWindow* window) {
	counter.draw(window);

	for (int y = 0; y < boardSize.y; y++) {
		for (int x = 0; x < boardSize.x; x++) {
			//std::cout << tileArr[y][x].getSprite().getPosition().x;
			tileArr[y][x].draw(window);
			if (flagArr[y][x].getIsRevealed()) {
				flagArr[y][x].draw(window);
			}
		}
	}

	if (bombsVisible) {
		for (int i = 0; i < numBombs; i++) {
			debugBombArr[i].draw(window);
		}
	}
}

const bool Board::checkWin() const{
	int numRevealed = 0;
	for (int x = 0; x < boardSize.x; x++) {
		for (int y = 0; y < boardSize.y; y++) {
			if (tileArr[y][x].getIsRevealed()) {
				numRevealed++;
			}
		}
	}
	if (numTiles - numRevealed == numBombs) {
		for (int x = 0; x < boardSize.x; x++) {
			for (int y = 0; y < boardSize.y; y++) {
				if (flagArr[y][x].getIsRevealed()) {
					flagArr[y][x].reveal();
				}
			}
		}
		for (int i = 0; i < numBombs; i++) {
			flagArr[debugBombArr[i].getBoardPosition().y][debugBombArr[i].getBoardPosition().x].reveal();
		}
		return true;
	}
	return false;
}

//interpret input
const Board::ClickResult& Board::interpretMouseClick(sf::Event event) {
	sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	sf::Vector2i tileIndex = getTileIndexFromExactPosition(mousePos);

	switch (event.mouseButton.button) {
	case sf::Mouse::Left:
		if (!flagArr[tileIndex.y][tileIndex.x].getIsRevealed())
		{
			if (tileArr[tileIndex.y][tileIndex.x].reveal()) {
				return LOSE;
			}
			if (checkWin()) {
				return WIN;
			}
		}
		return NEUTRAL;
		
		break;
	case sf::Mouse::Right:
		if (!tileArr[tileIndex.y][tileIndex.x].getIsRevealed()) {
			if (flagArr[tileIndex.y][tileIndex.x].reveal()) {
				tileArr[tileIndex.y][tileIndex.x].setIsFlagged(true);
				counter.operator--();
			}
			else {
				tileArr[tileIndex.y][tileIndex.x].setIsFlagged(false);
				counter.operator++();
			}
		}
		return NEUTRAL;
		break;
	}
}

//Destructor
Board::~Board() {
	clearBombs(); //called to delete bombLocations pointers
	for (int i = 0; i < boardSize.y; i++) {
		//delete each row of tiles
		delete[] tileArr[i];
	}
}