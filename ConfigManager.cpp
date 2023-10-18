#include "ConfigManager.h"

sf::Vector2<int> ConfigManager::boardSize;
int ConfigManager::numMines;
std::unordered_map<std::string, std::string> ConfigManager::setups;

const sf::Vector2<int>& ConfigManager::getBoardSize() {
	return boardSize;
}

const int& ConfigManager::getDefaultNumMines() {
	return numMines;
}

const std::string& ConfigManager::getSetup(const std::string& name) {
	return setups[name];
}

void ConfigManager::load(std::string& fileLocation) {
	std::ifstream configFile(fileLocation + "/config.cfg");

	int x;
	int y;
	configFile >> x;
	configFile >> y;
	configFile >> numMines;

	boardSize = sf::Vector2<int>(x, y);

	std::string setupNames[5] = { "lots_o_mines", "recursion_test", "testboard1", "testboard2", "testboard3" };
	for (std::string setupName : setupNames) {
		std::ifstream boardSetup(fileLocation + "/" + setupName + ".brd");
		std::string setup = "";
		for (std::string line; std::getline(boardSetup, line); )
		{
			setup += line;
		}
		setups.emplace(setupName, setup);
	}
}

void ConfigManager::clear() {
	setups.clear();
}