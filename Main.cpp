#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	Game game = Game();
	std::string imagesFile = "images";
	TextureManager::loadMinesweeperTextures(imagesFile);
	std::string boardsFile = "boards";
	ConfigManager::load(boardsFile);

	game.Start(ConfigManager::getBoardSize(), ConfigManager::getDefaultNumMines());

	while (game.Process()) {}

	TextureManager::clear();
	ConfigManager::clear();
}