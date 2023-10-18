#include "Game.h"


Game::Game() {
	isRunning = false;
	isAlive = false;
	board = nullptr;
	window = nullptr;
}

void Game::Start(const sf::Vector2<int>& boardSize, const unsigned int& numBombs) {
	const unsigned int randSeed = 0;

	isRunning = true;
	isAlive = true;
	if (board != nullptr) {
		board->~Board();
	}
	board = new Board(boardSize);

	sf::Vector2<float> boardPixelSize = sf::Vector2<float>(boardSize.x * board->TILE_SIZE.x,
		boardSize.y * board->TILE_SIZE.y);
	if (window == nullptr) {
		window = new sf::RenderWindow(sf::VideoMode(boardPixelSize.x, boardPixelSize.y + LOWER_MARGIN), "Minesweeper", sf::Style::Default);
	}

	//Set Button Positions
	restartButton.setPosition(sf::Vector2<float>(boardPixelSize.x / 2 - 32, boardPixelSize.y));
	debugButton.setPosition(sf::Vector2<float>(boardPixelSize.x / 2 + 96, boardPixelSize.y));
	for (int i = 0; i < 3; i++) {
		testButtons[i].setPosition(sf::Vector2<float>(boardPixelSize.x / 2 + 160 + (64 * i), boardPixelSize.y));
	}
	//Set Button Textures
	restartButton.setTexture(TextureManager::getTexture("face_happy"));
	debugButton.setTexture(TextureManager::getTexture("debug"));
	for (int i = 0; i < 3; i++) {
		testButtons[i].setTexture(TextureManager::getTexture("test_" + std::to_string(1 + i)));
	}

	board->assignRandomBombs(numBombs);
}

const bool& Game::Process() {
	if (window->isOpen()) {
		window->clear(sf::Color::White);

		sf::Event event;
		while (window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:				
				if (event.mouseButton.y < board->getBoardSize().y * board->TILE_SIZE.y && isAlive) {
					//if the mouse button is clicked inside the mine area
					switch (board->interpretMouseClick(event)) {
					case Board::NEUTRAL:
						break;
					case Board::WIN:
						restartButton.setTexture(TextureManager::getTexture("face_win"));
						isAlive = false;
						break;
					case Board::LOSE:
						restartButton.setTexture(TextureManager::getTexture("face_lose"));
						board->setBombVisibility(true);
						isAlive = false;
						break;
					}
				}
				else {
					sf::Vector2<float> mousePos = sf::Vector2<float>(event.mouseButton.x, event.mouseButton.y);
					if (restartButton.checkClick(mousePos)) {
						this->Start(ConfigManager::getBoardSize(), ConfigManager::getDefaultNumMines());
					}
					if (debugButton.checkClick(mousePos) && isAlive) {
						board->setBombVisibility(!board->getBombVisibility());
					}
					for (int i = 0; i < 3; i++) {
						if (testButtons[i].checkClick(mousePos)) {
							this->Start(ConfigManager::getBoardSize(), 0);
							board->assignSpecificBombs(ConfigManager::getSetup("testboard" + std::to_string(i + 1)));
						}
					}
				}
				break;
			case sf::Event::Closed:
				isRunning = false;
				window->close();
				break;
			}
		}
		board->drawBoard(window);

		restartButton.draw(window);
		debugButton.draw(window);
		for (int i = 0; i < 3; i++) {
			testButtons[i].draw(window);
		}


		window->display();
	}
	else {
		isRunning = false;
	}
	return isRunning;
}

Game::~Game() {
	delete board;
	delete window;
}